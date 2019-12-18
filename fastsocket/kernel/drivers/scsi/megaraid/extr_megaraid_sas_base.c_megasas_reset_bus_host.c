#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_1__* device; } ;
struct megasas_instance {TYPE_2__* pdev; } ;
struct TYPE_6__ {scalar_t__ hostdata; } ;
struct TYPE_5__ {scalar_t__ device; } ;
struct TYPE_4__ {TYPE_3__* host; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_LSI_FURY ; 
 scalar_t__ PCI_DEVICE_ID_LSI_FUSION ; 
 scalar_t__ PCI_DEVICE_ID_LSI_INVADER ; 
 int megasas_generic_reset (struct scsi_cmnd*) ; 
 int megasas_reset_fusion (TYPE_3__*) ; 

__attribute__((used)) static int megasas_reset_bus_host(struct scsi_cmnd *scmd)
{
	int ret;
	struct megasas_instance *instance;
	instance = (struct megasas_instance *)scmd->device->host->hostdata;

	/*
	 * First wait for all commands to complete
	 */
	if ((instance->pdev->device == PCI_DEVICE_ID_LSI_FUSION) ||
	    (instance->pdev->device == PCI_DEVICE_ID_LSI_INVADER) ||
	    (instance->pdev->device == PCI_DEVICE_ID_LSI_FURY))
		ret = megasas_reset_fusion(scmd->device->host);
	else
		ret = megasas_generic_reset(scmd);

	return ret;
}