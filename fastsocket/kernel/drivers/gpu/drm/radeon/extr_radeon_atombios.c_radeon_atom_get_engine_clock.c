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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  ulReturnEngineClock; } ;
typedef  TYPE_2__ GET_ENGINE_CLOCK_PS_ALLOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  GetEngineClock ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

uint32_t radeon_atom_get_engine_clock(struct radeon_device *rdev)
{
	GET_ENGINE_CLOCK_PS_ALLOCATION args;
	int index = GetIndexIntoMasterTable(COMMAND, GetEngineClock);

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
	return le32_to_cpu(args.ulReturnEngineClock);
}