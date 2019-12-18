#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ ether; scalar_t__ main; struct TYPE_4__* next; } ;
typedef  TYPE_1__ pvc_device ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_5__ {int dce_changed; scalar_t__ dce_pvc_count; TYPE_1__* first_pvc; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_2__* state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice (scalar_t__) ; 

__attribute__((used)) static void fr_destroy(struct net_device *frad)
{
	hdlc_device *hdlc = dev_to_hdlc(frad);
	pvc_device *pvc = state(hdlc)->first_pvc;
	state(hdlc)->first_pvc = NULL; /* All PVCs destroyed */
	state(hdlc)->dce_pvc_count = 0;
	state(hdlc)->dce_changed = 1;

	while (pvc) {
		pvc_device *next = pvc->next;
		/* destructors will free_netdev() main and ether */
		if (pvc->main)
			unregister_netdevice(pvc->main);

		if (pvc->ether)
			unregister_netdevice(pvc->ether);

		kfree(pvc);
		pvc = next;
	}
}