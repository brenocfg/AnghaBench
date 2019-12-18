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
struct pcmcia_device {int /*<<< orphan*/ * priv; } ;
struct TYPE_2__ {int stop; } ;
typedef  TYPE_1__ scsi_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  NSP_DEBUG_INIT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsp_cs_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 

__attribute__((used)) static void nsp_cs_detach(struct pcmcia_device *link)
{
	nsp_dbg(NSP_DEBUG_INIT, "in, link=0x%p", link);

	((scsi_info_t *)link->priv)->stop = 1;
	nsp_cs_release(link);

	kfree(link->priv);
	link->priv = NULL;
}