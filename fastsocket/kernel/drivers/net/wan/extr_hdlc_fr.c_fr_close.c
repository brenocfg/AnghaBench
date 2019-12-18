#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* next; scalar_t__ ether; scalar_t__ main; } ;
typedef  TYPE_1__ pvc_device ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_4__ {TYPE_1__* first_pvc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_close (scalar_t__) ; 
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 TYPE_2__* state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fr_close(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	pvc_device *pvc = state(hdlc)->first_pvc;

	while (pvc) {		/* Shutdown all PVCs for this FRAD */
		if (pvc->main)
			dev_close(pvc->main);
		if (pvc->ether)
			dev_close(pvc->ether);
		pvc = pvc->next;
	}
}