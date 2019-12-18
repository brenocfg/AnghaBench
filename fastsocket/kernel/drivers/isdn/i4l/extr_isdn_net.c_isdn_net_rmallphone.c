#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ isdn_net_phone ;
struct TYPE_8__ {TYPE_1__* local; } ;
typedef  TYPE_3__ isdn_net_dev ;
struct TYPE_6__ {int /*<<< orphan*/ * dial; TYPE_2__** phone; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static int
isdn_net_rmallphone(isdn_net_dev * p)
{
	isdn_net_phone *n;
	isdn_net_phone *m;
	int i;

	for (i = 0; i < 2; i++) {
		n = p->local->phone[i];
		while (n) {
			m = n->next;
			kfree(n);
			n = m;
		}
		p->local->phone[i] = NULL;
	}
	p->local->dial = NULL;
	return 0;
}