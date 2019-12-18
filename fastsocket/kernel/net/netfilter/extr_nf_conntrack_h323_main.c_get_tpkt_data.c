#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int doff; } ;
struct sk_buff {int len; } ;
struct nf_ct_h323_master {int* tpkt_len; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  _tcph ;
struct TYPE_3__ {struct nf_ct_h323_master ct_h323_info; } ;
struct TYPE_4__ {TYPE_1__ help; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int CTINFO2DIR (int) ; 
 struct tcphdr* h323_buffer ; 
 scalar_t__ net_ratelimit () ; 
 TYPE_2__* nfct_help (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  printk (char*) ; 
 void* skb_header_pointer (struct sk_buff*,int,int,struct tcphdr*) ; 

__attribute__((used)) static int get_tpkt_data(struct sk_buff *skb, unsigned int protoff,
			 struct nf_conn *ct, enum ip_conntrack_info ctinfo,
			 unsigned char **data, int *datalen, int *dataoff)
{
	struct nf_ct_h323_master *info = &nfct_help(ct)->help.ct_h323_info;
	int dir = CTINFO2DIR(ctinfo);
	const struct tcphdr *th;
	struct tcphdr _tcph;
	int tcpdatalen;
	int tcpdataoff;
	unsigned char *tpkt;
	int tpktlen;
	int tpktoff;

	/* Get TCP header */
	th = skb_header_pointer(skb, protoff, sizeof(_tcph), &_tcph);
	if (th == NULL)
		return 0;

	/* Get TCP data offset */
	tcpdataoff = protoff + th->doff * 4;

	/* Get TCP data length */
	tcpdatalen = skb->len - tcpdataoff;
	if (tcpdatalen <= 0)	/* No TCP data */
		goto clear_out;

	if (*data == NULL) {	/* first TPKT */
		/* Get first TPKT pointer */
		tpkt = skb_header_pointer(skb, tcpdataoff, tcpdatalen,
					  h323_buffer);
		BUG_ON(tpkt == NULL);

		/* Validate TPKT identifier */
		if (tcpdatalen < 4 || tpkt[0] != 0x03 || tpkt[1] != 0) {
			/* Netmeeting sends TPKT header and data separately */
			if (info->tpkt_len[dir] > 0) {
				pr_debug("nf_ct_h323: previous packet "
					 "indicated separate TPKT data of %hu "
					 "bytes\n", info->tpkt_len[dir]);
				if (info->tpkt_len[dir] <= tcpdatalen) {
					/* Yes, there was a TPKT header
					 * received */
					*data = tpkt;
					*datalen = info->tpkt_len[dir];
					*dataoff = 0;
					goto out;
				}

				/* Fragmented TPKT */
				pr_debug("nf_ct_h323: fragmented TPKT\n");
				goto clear_out;
			}

			/* It is not even a TPKT */
			return 0;
		}
		tpktoff = 0;
	} else {		/* Next TPKT */
		tpktoff = *dataoff + *datalen;
		tcpdatalen -= tpktoff;
		if (tcpdatalen <= 4)	/* No more TPKT */
			goto clear_out;
		tpkt = *data + *datalen;

		/* Validate TPKT identifier */
		if (tpkt[0] != 0x03 || tpkt[1] != 0)
			goto clear_out;
	}

	/* Validate TPKT length */
	tpktlen = tpkt[2] * 256 + tpkt[3];
	if (tpktlen < 4)
		goto clear_out;
	if (tpktlen > tcpdatalen) {
		if (tcpdatalen == 4) {	/* Separate TPKT header */
			/* Netmeeting sends TPKT header and data separately */
			pr_debug("nf_ct_h323: separate TPKT header indicates "
				 "there will be TPKT data of %hu bytes\n",
				 tpktlen - 4);
			info->tpkt_len[dir] = tpktlen - 4;
			return 0;
		}

		if (net_ratelimit())
			printk("nf_ct_h323: incomplete TPKT (fragmented?)\n");
		goto clear_out;
	}

	/* This is the encapsulated data */
	*data = tpkt + 4;
	*datalen = tpktlen - 4;
	*dataoff = tpktoff + 4;

      out:
	/* Clear TPKT length */
	info->tpkt_len[dir] = 0;
	return 1;

      clear_out:
	info->tpkt_len[dir] = 0;
	return 0;
}