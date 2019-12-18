#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* len; void* offset; void* page; } ;
struct TYPE_6__ {scalar_t__ dlstate; void* dltimeout; TYPE_4__ bufinfo; scalar_t__* port_enabled; } ;
typedef  TYPE_1__ hfa384x_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HFA384x_DLSTATE_DISABLED ; 
 scalar_t__ HFA384x_DLSTATE_FLASHENABLED ; 
 int HFA384x_PORTID_MAX ; 
 int /*<<< orphan*/  HFA384x_RID_DOWNLOADBUFFER ; 
 int /*<<< orphan*/  HFA384x_RID_MAXLOADTIME ; 
 int hfa384x_drvr_getconfig (TYPE_1__*,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int hfa384x_drvr_getconfig16 (TYPE_1__*,int /*<<< orphan*/ ,void**) ; 
 void* le16_to_cpu (void*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int hfa384x_drvr_flashdl_enable(hfa384x_t *hw)
{
	int result = 0;
	int i;

	/* Check that a port isn't active */
	for (i = 0; i < HFA384x_PORTID_MAX; i++) {
		if (hw->port_enabled[i]) {
			pr_debug("called when port enabled.\n");
			return -EINVAL;
		}
	}

	/* Check that we're not already in a download state */
	if (hw->dlstate != HFA384x_DLSTATE_DISABLED)
		return -EINVAL;

	/* Retrieve the buffer loc&size and timeout */
	if ((result = hfa384x_drvr_getconfig(hw, HFA384x_RID_DOWNLOADBUFFER,
					     &(hw->bufinfo),
					     sizeof(hw->bufinfo)))) {
		return result;
	}
	hw->bufinfo.page = le16_to_cpu(hw->bufinfo.page);
	hw->bufinfo.offset = le16_to_cpu(hw->bufinfo.offset);
	hw->bufinfo.len = le16_to_cpu(hw->bufinfo.len);
	if ((result = hfa384x_drvr_getconfig16(hw, HFA384x_RID_MAXLOADTIME,
					       &(hw->dltimeout)))) {
		return result;
	}
	hw->dltimeout = le16_to_cpu(hw->dltimeout);

	pr_debug("flashdl_enable\n");

	hw->dlstate = HFA384x_DLSTATE_FLASHENABLED;

	return result;
}