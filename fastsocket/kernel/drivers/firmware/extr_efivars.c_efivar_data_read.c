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
struct efi_variable {int /*<<< orphan*/  DataSize; int /*<<< orphan*/  Data; } ;
struct efivar_entry {int /*<<< orphan*/  efivars; struct efi_variable var; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ efi_status_t ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ get_var_data (int /*<<< orphan*/ ,struct efi_variable*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
efivar_data_read(struct efivar_entry *entry, char *buf)
{
	struct efi_variable *var = &entry->var;
	efi_status_t status;

	if (!entry || !buf)
		return -EINVAL;

	status = get_var_data(entry->efivars, var);
	if (status != EFI_SUCCESS)
		return -EIO;

	memcpy(buf, var->Data, var->DataSize);
	return var->DataSize;
}