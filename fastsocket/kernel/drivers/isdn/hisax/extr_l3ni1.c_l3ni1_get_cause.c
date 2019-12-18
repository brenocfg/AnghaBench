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
typedef  int u_char ;
struct sk_buff {int* data; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int cause; int loc; int /*<<< orphan*/ * diag; } ;
struct l3_process {TYPE_1__ para; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE_CAUSE ; 
 int* findie (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
l3ni1_get_cause(struct l3_process *pc, struct sk_buff *skb) {
	u_char l, i=0;
	u_char *p;

	p = skb->data;
	pc->para.cause = 31;
	pc->para.loc = 0;
	if ((p = findie(p, skb->len, IE_CAUSE, 0))) {
		p++;
		l = *p++;
		if (l>30)
			return(1);
		if (l) {
			pc->para.loc = *p++;
			l--;
		} else {
			return(2);
		}
		if (l && !(pc->para.loc & 0x80)) {
			l--;
			p++; /* skip recommendation */
		}
		if (l) {
			pc->para.cause = *p++;
			l--;
			if (!(pc->para.cause & 0x80))
				return(3);
		} else
			return(4);
		while (l && (i<6)) {
			pc->para.diag[i++] = *p++;
			l--;
		}
	} else
		return(-1);
	return(0);
}