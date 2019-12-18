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
struct sk_buff {int dummy; } ;
struct rtattr {int rta_type; int rta_len; } ;

/* Variables and functions */
 scalar_t__ RTA_ALIGN (int) ; 
 scalar_t__ RTA_DATA (struct rtattr*) ; 
 int RTA_LENGTH (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ skb_put (struct sk_buff*,scalar_t__) ; 

void __rta_fill(struct sk_buff *skb, int attrtype, int attrlen, const void *data)
{
	struct rtattr *rta;
	int size = RTA_LENGTH(attrlen);

	rta = (struct rtattr*)skb_put(skb, RTA_ALIGN(size));
	rta->rta_type = attrtype;
	rta->rta_len = size;
	memcpy(RTA_DATA(rta), data, attrlen);
	memset(RTA_DATA(rta) + attrlen, 0, RTA_ALIGN(size) - size);
}