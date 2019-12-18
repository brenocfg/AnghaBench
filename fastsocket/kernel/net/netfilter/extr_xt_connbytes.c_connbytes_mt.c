#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int64_t ;
struct xt_match_param {struct xt_connbytes_info* matchinfo; } ;
struct TYPE_2__ {scalar_t__ to; scalar_t__ from; } ;
struct xt_connbytes_info {int what; TYPE_1__ count; int /*<<< orphan*/  direction; } ;
struct sk_buff {int dummy; } ;
struct nf_conn_counter {scalar_t__ packets; scalar_t__ bytes; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 size_t IP_CT_DIR_ORIGINAL ; 
 size_t IP_CT_DIR_REPLY ; 
#define  XT_CONNBYTES_AVGPKT 133 
#define  XT_CONNBYTES_BYTES 132 
#define  XT_CONNBYTES_DIR_BOTH 131 
#define  XT_CONNBYTES_DIR_ORIGINAL 130 
#define  XT_CONNBYTES_DIR_REPLY 129 
#define  XT_CONNBYTES_PKTS 128 
 scalar_t__ div64_u64 (scalar_t__,scalar_t__) ; 
 struct nf_conn_counter* nf_conn_acct_find (struct nf_conn const*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 

__attribute__((used)) static bool
connbytes_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_connbytes_info *sinfo = par->matchinfo;
	const struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	u_int64_t what = 0;	/* initialize to make gcc happy */
	u_int64_t bytes = 0;
	u_int64_t pkts = 0;
	const struct nf_conn_counter *counters;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		return false;

	counters = nf_conn_acct_find(ct);
	if (!counters)
		return false;

	switch (sinfo->what) {
	case XT_CONNBYTES_PKTS:
		switch (sinfo->direction) {
		case XT_CONNBYTES_DIR_ORIGINAL:
			what = counters[IP_CT_DIR_ORIGINAL].packets;
			break;
		case XT_CONNBYTES_DIR_REPLY:
			what = counters[IP_CT_DIR_REPLY].packets;
			break;
		case XT_CONNBYTES_DIR_BOTH:
			what = counters[IP_CT_DIR_ORIGINAL].packets;
			what += counters[IP_CT_DIR_REPLY].packets;
			break;
		}
		break;
	case XT_CONNBYTES_BYTES:
		switch (sinfo->direction) {
		case XT_CONNBYTES_DIR_ORIGINAL:
			what = counters[IP_CT_DIR_ORIGINAL].bytes;
			break;
		case XT_CONNBYTES_DIR_REPLY:
			what = counters[IP_CT_DIR_REPLY].bytes;
			break;
		case XT_CONNBYTES_DIR_BOTH:
			what = counters[IP_CT_DIR_ORIGINAL].bytes;
			what += counters[IP_CT_DIR_REPLY].bytes;
			break;
		}
		break;
	case XT_CONNBYTES_AVGPKT:
		switch (sinfo->direction) {
		case XT_CONNBYTES_DIR_ORIGINAL:
			bytes = counters[IP_CT_DIR_ORIGINAL].bytes;
			pkts  = counters[IP_CT_DIR_ORIGINAL].packets;
			break;
		case XT_CONNBYTES_DIR_REPLY:
			bytes = counters[IP_CT_DIR_REPLY].bytes;
			pkts  = counters[IP_CT_DIR_REPLY].packets;
			break;
		case XT_CONNBYTES_DIR_BOTH:
			bytes = counters[IP_CT_DIR_ORIGINAL].bytes +
				counters[IP_CT_DIR_REPLY].bytes;
			pkts  = counters[IP_CT_DIR_ORIGINAL].packets +
				counters[IP_CT_DIR_REPLY].packets;
			break;
		}
		if (pkts != 0)
			what = div64_u64(bytes, pkts);
		break;
	}

	if (sinfo->count.to)
		return what <= sinfo->count.to && what >= sinfo->count.from;
	else
		return what >= sinfo->count.from;
}