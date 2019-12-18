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
typedef  int u_char ;
struct sk_buff {int* data; int /*<<< orphan*/  len; } ;
struct l3_process {int debug; int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE_CHANNEL_ID ; 
 int L3_DEB_WARN ; 
 int* findie (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l3_debug (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
l3dss1_get_channel_id(struct l3_process *pc, struct sk_buff *skb) {
	u_char *p;

	p = skb->data;
	if ((p = findie(p, skb->len, IE_CHANNEL_ID, 0))) {
		p++;
		if (*p != 1) { /* len for BRI = 1 */
			if (pc->debug & L3_DEB_WARN)
				l3_debug(pc->st, "wrong chid len %d", *p);
			return (-2);
		}
		p++;
		if (*p & 0x60) { /* only base rate interface */
			if (pc->debug & L3_DEB_WARN)
				l3_debug(pc->st, "wrong chid %x", *p);
			return (-3);
		}
		return(*p & 0x3);
	} else
		return(-1);
}