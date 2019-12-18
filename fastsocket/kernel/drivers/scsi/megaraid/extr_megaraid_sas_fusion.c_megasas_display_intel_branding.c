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
struct megasas_instance {TYPE_2__* host; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_3__ {scalar_t__ subsystem_vendor; int device; int /*<<< orphan*/  dev; int /*<<< orphan*/  subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEGARAID_INTEL_RS3DC040_BRANDING ; 
#define  MEGARAID_INTEL_RS3DC040_SSDID 135 
 int /*<<< orphan*/  MEGARAID_INTEL_RS3DC080_BRANDING ; 
#define  MEGARAID_INTEL_RS3DC080_SSDID 134 
 int /*<<< orphan*/  MEGARAID_INTEL_RS3MC044_BRANDING ; 
#define  MEGARAID_INTEL_RS3MC044_SSDID 133 
 int /*<<< orphan*/  MEGARAID_INTEL_RS3SC008_BRANDING ; 
#define  MEGARAID_INTEL_RS3SC008_SSDID 132 
 int /*<<< orphan*/  MEGARAID_INTEL_RS3WC040_BRANDING ; 
#define  MEGARAID_INTEL_RS3WC040_SSDID 131 
 int /*<<< orphan*/  MEGARAID_INTEL_RS3WC080_BRANDING ; 
#define  MEGARAID_INTEL_RS3WC080_SSDID 130 
#define  PCI_DEVICE_ID_LSI_FURY 129 
#define  PCI_DEVICE_ID_LSI_INVADER 128 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
megasas_display_intel_branding(struct megasas_instance *instance)
{
	if (instance->pdev->subsystem_vendor != PCI_VENDOR_ID_INTEL)
		return;

	switch (instance->pdev->device) {
	case PCI_DEVICE_ID_LSI_INVADER:
		switch (instance->pdev->subsystem_device) {
		case MEGARAID_INTEL_RS3DC080_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3DC080_BRANDING);
			break;
		case MEGARAID_INTEL_RS3DC040_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3DC040_BRANDING);
			break;
		case MEGARAID_INTEL_RS3SC008_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3SC008_BRANDING);
			break;
		case MEGARAID_INTEL_RS3MC044_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3MC044_BRANDING);
			break;
		default:
			break;
		}
		break;
	case PCI_DEVICE_ID_LSI_FURY:
		switch (instance->pdev->subsystem_device) {
		case MEGARAID_INTEL_RS3WC080_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3WC080_BRANDING);
			break;
		case MEGARAID_INTEL_RS3WC040_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3WC040_BRANDING);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}