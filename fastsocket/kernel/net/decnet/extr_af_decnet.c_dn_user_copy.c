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
typedef  int u16 ;
struct sk_buff {unsigned char* data; } ;
struct optdata_dn {int /*<<< orphan*/  opt_data; scalar_t__ opt_status; int /*<<< orphan*/  opt_optl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void dn_user_copy(struct sk_buff *skb, struct optdata_dn *opt)
{
	unsigned char *ptr = skb->data;
	u16 len = *ptr++; /* yes, it's 8bit on the wire */

	BUG_ON(len > 16); /* we've checked the contents earlier */
	opt->opt_optl   = cpu_to_le16(len);
	opt->opt_status = 0;
	memcpy(opt->opt_data, ptr, len);
	skb_pull(skb, len + 1);
}