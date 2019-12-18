#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/  num; } ;
typedef  TYPE_2__ isdn_net_phone ;
struct TYPE_10__ {int outgoing; int /*<<< orphan*/  phone; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ isdn_net_ioctl_phone ;
struct TYPE_11__ {TYPE_1__* local; } ;
typedef  TYPE_4__ isdn_net_dev ;
struct TYPE_8__ {TYPE_2__** phone; TYPE_2__* dial; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 TYPE_4__* isdn_net_findif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
isdn_net_delphone(isdn_net_ioctl_phone * phone)
{
	isdn_net_dev *p = isdn_net_findif(phone->name);
	int inout = phone->outgoing & 1;
	isdn_net_phone *n;
	isdn_net_phone *m;

	if (p) {
		n = p->local->phone[inout];
		m = NULL;
		while (n) {
			if (!strcmp(n->num, phone->phone)) {
				if (p->local->dial == n)
					p->local->dial = n->next;
				if (m)
					m->next = n->next;
				else
					p->local->phone[inout] = n->next;
				kfree(n);
				return 0;
			}
			m = n;
			n = (isdn_net_phone *) n->next;
		}
		return -EINVAL;
	}
	return -ENODEV;
}