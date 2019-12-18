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
struct ipmi_device_id {scalar_t__ manufacturer_id; } ;
struct smi_info {scalar_t__ si_type; struct ipmi_device_id device_id; } ;

/* Variables and functions */
 scalar_t__ DELL_IANA_MFR_ID ; 
 scalar_t__ SI_BT ; 
 int /*<<< orphan*/  dell_poweredge_bt_xaction_notifier ; 
 int /*<<< orphan*/  register_xaction_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
setup_dell_poweredge_bt_xaction_handler(struct smi_info *smi_info)
{
	struct ipmi_device_id *id = &smi_info->device_id;
	if (id->manufacturer_id == DELL_IANA_MFR_ID &&
	    smi_info->si_type == SI_BT)
		register_xaction_notifier(&dell_poweredge_bt_xaction_notifier);
}