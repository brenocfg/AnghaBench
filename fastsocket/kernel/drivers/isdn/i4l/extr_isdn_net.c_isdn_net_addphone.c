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
struct TYPE_8__ {TYPE_2__** phone; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_4__* isdn_net_findif (int /*<<< orphan*/ ) ; 
 TYPE_2__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
isdn_net_addphone(isdn_net_ioctl_phone * phone)
{
	isdn_net_dev *p = isdn_net_findif(phone->name);
	isdn_net_phone *n;

	if (p) {
		if (!(n = kmalloc(sizeof(isdn_net_phone), GFP_KERNEL)))
			return -ENOMEM;
		strlcpy(n->num, phone->phone, sizeof(n->num));
		n->next = p->local->phone[phone->outgoing & 1];
		p->local->phone[phone->outgoing & 1] = n;
		return 0;
	}
	return -ENODEV;
}