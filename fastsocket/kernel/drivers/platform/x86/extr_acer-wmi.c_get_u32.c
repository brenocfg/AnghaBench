#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
#define  ACER_AMW0 130 
#define  ACER_AMW0_V2 129 
 int /*<<< orphan*/  ACER_CAP_MAILLED ; 
#define  ACER_WMID 128 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AMW0_get_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  WMID_get_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* interface ; 

__attribute__((used)) static acpi_status get_u32(u32 *value, u32 cap)
{
	acpi_status status = AE_ERROR;

	switch (interface->type) {
	case ACER_AMW0:
		status = AMW0_get_u32(value, cap, interface);
		break;
	case ACER_AMW0_V2:
		if (cap == ACER_CAP_MAILLED) {
			status = AMW0_get_u32(value, cap, interface);
			break;
		}
	case ACER_WMID:
		status = WMID_get_u32(value, cap, interface);
		break;
	}

	return status;
}