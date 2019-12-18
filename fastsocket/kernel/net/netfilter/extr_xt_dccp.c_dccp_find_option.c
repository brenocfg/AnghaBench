#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned char const u_int8_t ;
struct sk_buff {int dummy; } ;
struct dccp_hdr {int dccph_doff; } ;

/* Variables and functions */
 int __dccp_hdr_len (struct dccp_hdr const*) ; 
 int /*<<< orphan*/  dccp_buflock ; 
 int /*<<< orphan*/  dccp_optbuf ; 
 unsigned char* skb_header_pointer (struct sk_buff const*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
dccp_find_option(u_int8_t option,
		 const struct sk_buff *skb,
		 unsigned int protoff,
		 const struct dccp_hdr *dh,
		 bool *hotdrop)
{
	/* tcp.doff is only 4 bits, ie. max 15 * 4 bytes */
	const unsigned char *op;
	unsigned int optoff = __dccp_hdr_len(dh);
	unsigned int optlen = dh->dccph_doff*4 - __dccp_hdr_len(dh);
	unsigned int i;

	if (dh->dccph_doff * 4 < __dccp_hdr_len(dh))
		goto invalid;

	if (!optlen)
		return false;

	spin_lock_bh(&dccp_buflock);
	op = skb_header_pointer(skb, protoff + optoff, optlen, dccp_optbuf);
	if (op == NULL) {
		/* If we don't have the whole header, drop packet. */
		goto partial;
	}

	for (i = 0; i < optlen; ) {
		if (op[i] == option) {
			spin_unlock_bh(&dccp_buflock);
			return true;
		}

		if (op[i] < 2)
			i++;
		else
			i += op[i+1]?:1;
	}

	spin_unlock_bh(&dccp_buflock);
	return false;

partial:
	spin_unlock_bh(&dccp_buflock);
invalid:
	*hotdrop = true;
	return false;
}