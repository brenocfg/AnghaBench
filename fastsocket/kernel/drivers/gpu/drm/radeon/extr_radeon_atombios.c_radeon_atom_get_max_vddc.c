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
struct TYPE_6__ {int ucVoltageType; int /*<<< orphan*/  usVoltageLevel; int /*<<< orphan*/  ucVoltageMode; } ;
struct TYPE_4__ {int /*<<< orphan*/  usVoltageLevel; int /*<<< orphan*/  ucVoltageMode; int /*<<< orphan*/  ucVoltageType; } ;
union set_voltage {TYPE_3__ v3; TYPE_1__ v2; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_2__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_GET_VOLTAGE_LEVEL ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int EINVAL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_VOLTAGE_GET_MAX_VOLTAGE ; 
 int /*<<< orphan*/  SetVoltage ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radeon_atom_get_max_vddc(struct radeon_device *rdev, u8 voltage_type,
				    u16 voltage_id, u16 *voltage)
{
	union set_voltage args;
	int index = GetIndexIntoMasterTable(COMMAND, SetVoltage);
	u8 frev, crev;

	if (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		return -EINVAL;

	switch (crev) {
	case 1:
		return -EINVAL;
	case 2:
		args.v2.ucVoltageType = SET_VOLTAGE_GET_MAX_VOLTAGE;
		args.v2.ucVoltageMode = 0;
		args.v2.usVoltageLevel = 0;

		atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);

		*voltage = le16_to_cpu(args.v2.usVoltageLevel);
		break;
	case 3:
		args.v3.ucVoltageType = voltage_type;
		args.v3.ucVoltageMode = ATOM_GET_VOLTAGE_LEVEL;
		args.v3.usVoltageLevel = cpu_to_le16(voltage_id);

		atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);

		*voltage = le16_to_cpu(args.v3.usVoltageLevel);
		break;
	default:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		return -EINVAL;
	}

	return 0;
}