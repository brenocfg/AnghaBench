#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dto_bss_size; int /*<<< orphan*/  dto_bss_va; int /*<<< orphan*/  dto_data_size; int /*<<< orphan*/  dto_data_va; int /*<<< orphan*/  dto_text_size; int /*<<< orphan*/  dto_text_va; int /*<<< orphan*/  dto_flags; int /*<<< orphan*/  dto_id; int /*<<< orphan*/  dto_file; int /*<<< orphan*/  dto_name; } ;
typedef  TYPE_1__ dtrace_objinfo_t ;
struct TYPE_7__ {int dm_flags; int /*<<< orphan*/  dm_bss_size; int /*<<< orphan*/  dm_bss_va; int /*<<< orphan*/  dm_data_size; int /*<<< orphan*/  dm_data_va; int /*<<< orphan*/  dm_text_size; int /*<<< orphan*/  dm_text_va; int /*<<< orphan*/  dm_modid; int /*<<< orphan*/  dm_file; int /*<<< orphan*/  dm_name; } ;
typedef  TYPE_2__ dt_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_OBJ_F_KERNEL ; 
 int /*<<< orphan*/  DTRACE_OBJ_F_PRIMARY ; 
 int DT_DM_KERNEL ; 
 int DT_DM_PRIMARY ; 

__attribute__((used)) static dtrace_objinfo_t *
dt_module_info(const dt_module_t *dmp, dtrace_objinfo_t *dto)
{
	dto->dto_name = dmp->dm_name;
	dto->dto_file = dmp->dm_file;
	dto->dto_id = dmp->dm_modid;
	dto->dto_flags = 0;

	if (dmp->dm_flags & DT_DM_KERNEL)
		dto->dto_flags |= DTRACE_OBJ_F_KERNEL;
	if (dmp->dm_flags & DT_DM_PRIMARY)
		dto->dto_flags |= DTRACE_OBJ_F_PRIMARY;

	dto->dto_text_va = dmp->dm_text_va;
	dto->dto_text_size = dmp->dm_text_size;
	dto->dto_data_va = dmp->dm_data_va;
	dto->dto_data_size = dmp->dm_data_size;
	dto->dto_bss_va = dmp->dm_bss_va;
	dto->dto_bss_size = dmp->dm_bss_size;

	return (dto);
}