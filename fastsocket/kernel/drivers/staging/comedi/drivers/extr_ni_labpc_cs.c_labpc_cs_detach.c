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
struct pcmcia_device {scalar_t__ priv; scalar_t__ dev_node; } ;
struct local_info_t {int stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  labpc_release (struct pcmcia_device*) ; 

__attribute__((used)) static void labpc_cs_detach(struct pcmcia_device *link)
{
	DEBUG(0, "labpc_cs_detach(0x%p)\n", link);

	/*
	   If the device is currently configured and active, we won't
	   actually delete it yet.  Instead, it is marked so that when
	   the release() function is called, that will trigger a proper
	   detach().
	 */
	if (link->dev_node) {
		((struct local_info_t *)link->priv)->stop = 1;
		labpc_release(link);
	}

	/* This points to the parent local_info_t struct */
	if (link->priv)
		kfree(link->priv);

}