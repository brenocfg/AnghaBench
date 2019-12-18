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
typedef  int u32 ;
struct wmi_interface {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int mailled; } ;

/* Variables and functions */
#define  ACER_CAP_BLUETOOTH 132 
#define  ACER_CAP_BRIGHTNESS 131 
#define  ACER_CAP_MAILLED 130 
#define  ACER_CAP_THREEG 129 
#define  ACER_CAP_WIRELESS 128 
 int ACER_WMID_SET_BLUETOOTH_METHODID ; 
 int ACER_WMID_SET_BRIGHTNESS_METHODID ; 
 int ACER_WMID_SET_THREEG_METHODID ; 
 int ACER_WMID_SET_WIRELESS_METHODID ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  WMI_execute_u32 (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i8042_command (char*,int) ; 
 int /*<<< orphan*/  i8042_lock_chip () ; 
 int /*<<< orphan*/  i8042_unlock_chip () ; 
 int max_brightness ; 
 TYPE_1__* quirks ; 

__attribute__((used)) static acpi_status WMID_set_u32(u32 value, u32 cap, struct wmi_interface *iface)
{
	u32 method_id = 0;
	char param;

	switch (cap) {
	case ACER_CAP_BRIGHTNESS:
		if (value > max_brightness)
			return AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_BRIGHTNESS_METHODID;
		break;
	case ACER_CAP_WIRELESS:
		if (value > 1)
			return AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_WIRELESS_METHODID;
		break;
	case ACER_CAP_BLUETOOTH:
		if (value > 1)
			return AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_BLUETOOTH_METHODID;
		break;
	case ACER_CAP_THREEG:
		if (value > 1)
			return AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_THREEG_METHODID;
		break;
	case ACER_CAP_MAILLED:
		if (value > 1)
			return AE_BAD_PARAMETER;
		if (quirks->mailled == 1) {
			param = value ? 0x92 : 0x93;
			i8042_lock_chip();
			i8042_command(&param, 0x1059);
			i8042_unlock_chip();
			return 0;
		}
		break;
	default:
		return AE_ERROR;
	}
	return WMI_execute_u32(method_id, (u32)value, NULL);
}