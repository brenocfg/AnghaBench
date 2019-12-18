#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {scalar_t__ win; int /*<<< orphan*/ * dev_node; TYPE_1__* priv; } ;
struct TYPE_5__ {TYPE_3__* host; } ;
typedef  TYPE_1__ scsi_info_t ;
struct TYPE_6__ {scalar_t__ MmioAddress; } ;
typedef  TYPE_2__ nsp_hw_data ;
struct TYPE_7__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  NSP_DEBUG_INIT ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  nsp_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_3__*) ; 
 int /*<<< orphan*/  scsi_remove_host (TYPE_3__*) ; 

__attribute__((used)) static void nsp_cs_release(struct pcmcia_device *link)
{
	scsi_info_t *info = link->priv;
	nsp_hw_data *data = NULL;

	if (info->host == NULL) {
		nsp_msg(KERN_DEBUG, "unexpected card release call.");
	} else {
		data = (nsp_hw_data *)info->host->hostdata;
	}

	nsp_dbg(NSP_DEBUG_INIT, "link=0x%p", link);

	/* Unlink the device chain */
	if (info->host != NULL) {
		scsi_remove_host(info->host);
	}
	link->dev_node = NULL;

	if (link->win) {
		if (data != NULL) {
			iounmap((void *)(data->MmioAddress));
		}
	}
	pcmcia_disable_device(link);

	if (info->host != NULL) {
		scsi_host_put(info->host);
	}
}