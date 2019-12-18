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
struct efi_variable {int Attributes; } ;
struct efivar_entry {int /*<<< orphan*/  efivars; struct efi_variable var; } ;
typedef  int ssize_t ;
typedef  scalar_t__ efi_status_t ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ get_var_data (int /*<<< orphan*/ ,struct efi_variable*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t
efivar_attr_read(struct efivar_entry *entry, char *buf)
{
	struct efi_variable *var = &entry->var;
	char *str = buf;
	efi_status_t status;

	if (!entry || !buf)
		return -EINVAL;

	status = get_var_data(entry->efivars, var);
	if (status != EFI_SUCCESS)
		return -EIO;

	if (var->Attributes & 0x1)
		str += sprintf(str, "EFI_VARIABLE_NON_VOLATILE\n");
	if (var->Attributes & 0x2)
		str += sprintf(str, "EFI_VARIABLE_BOOTSERVICE_ACCESS\n");
	if (var->Attributes & 0x4)
		str += sprintf(str, "EFI_VARIABLE_RUNTIME_ACCESS\n");
	return str - buf;
}