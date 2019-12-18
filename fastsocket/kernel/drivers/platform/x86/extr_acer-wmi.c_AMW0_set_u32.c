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
struct wmab_args {int ebx; scalar_t__ edx; scalar_t__ ecx; int /*<<< orphan*/  eax; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; } ;

/* Variables and functions */
 int ACER_AMW0_BLUETOOTH_MASK ; 
 int ACER_AMW0_MAILLED_MASK ; 
 int ACER_AMW0_WIRELESS_MASK ; 
 int /*<<< orphan*/  ACER_AMW0_WRITE ; 
#define  ACER_CAP_BLUETOOTH 131 
#define  ACER_CAP_BRIGHTNESS 130 
#define  ACER_CAP_MAILLED 129 
#define  ACER_CAP_WIRELESS 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  ec_write (int,int) ; 
 int max_brightness ; 
 TYPE_1__* quirks ; 
 int /*<<< orphan*/  wmab_execute (struct wmab_args*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status AMW0_set_u32(u32 value, u32 cap, struct wmi_interface *iface)
{
	struct wmab_args args;

	args.eax = ACER_AMW0_WRITE;
	args.ebx = value ? (1<<8) : 0;
	args.ecx = args.edx = 0;

	switch (cap) {
	case ACER_CAP_MAILLED:
		if (value > 1)
			return AE_BAD_PARAMETER;
		args.ebx |= ACER_AMW0_MAILLED_MASK;
		break;
	case ACER_CAP_WIRELESS:
		if (value > 1)
			return AE_BAD_PARAMETER;
		args.ebx |= ACER_AMW0_WIRELESS_MASK;
		break;
	case ACER_CAP_BLUETOOTH:
		if (value > 1)
			return AE_BAD_PARAMETER;
		args.ebx |= ACER_AMW0_BLUETOOTH_MASK;
		break;
	case ACER_CAP_BRIGHTNESS:
		if (value > max_brightness)
			return AE_BAD_PARAMETER;
		switch (quirks->brightness) {
		default:
			return ec_write(0x83, value);
			break;
		}
	default:
		return AE_ERROR;
	}

	/* Actually do the set */
	return wmab_execute(&args, NULL);
}