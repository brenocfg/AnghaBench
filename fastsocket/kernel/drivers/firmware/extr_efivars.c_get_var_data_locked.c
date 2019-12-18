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
struct efivars {TYPE_1__* ops; } ;
struct efi_variable {int DataSize; int /*<<< orphan*/  Data; int /*<<< orphan*/  Attributes; int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/  VariableName; } ;
typedef  int /*<<< orphan*/  efi_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_variable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static efi_status_t
get_var_data_locked(struct efivars *efivars, struct efi_variable *var)
{
	efi_status_t status;

	var->DataSize = 1024;
	status = efivars->ops->get_variable(var->VariableName,
					    &var->VendorGuid,
					    &var->Attributes,
					    &var->DataSize,
					    var->Data);
	return status;
}