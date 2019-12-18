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
struct work_struct {int dummy; } ;
struct efivars {int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;
struct TYPE_2__ {scalar_t__ (* get_next_variable ) (unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ EFI_NOT_FOUND ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct efivars __efivars ; 
 int /*<<< orphan*/  efivar_create_sysfs_entry (struct efivars*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long var_name_strnsize (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  variable_is_present (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efivar_update_sysfs_entries(struct work_struct *work)
{
	struct efivars *efivars = &__efivars;
	efi_guid_t vendor;
	efi_char16_t *variable_name;
	unsigned long variable_name_size = 1024;
	efi_status_t status = EFI_NOT_FOUND;
	bool found;

	/* Add new sysfs entries */
	while (1) {
		variable_name = kzalloc(variable_name_size, GFP_KERNEL);
		if (!variable_name) {
			pr_err("efivars: Memory allocation failed.\n");
			return;
		}

		spin_lock_irq(&efivars->lock);
		found = false;
		while (1) {
			variable_name_size = 1024;
			status = efivars->ops->get_next_variable(
							&variable_name_size,
							variable_name,
							&vendor);
			if (status != EFI_SUCCESS) {
				break;
			} else {
				if (!variable_is_present(variable_name,
				    &vendor)) {
					found = true;
					break;
				}
			}
		}
		spin_unlock_irq(&efivars->lock);

		if (!found) {
			kfree(variable_name);
			break;
		} else {
			variable_name_size = var_name_strnsize(variable_name,
							       variable_name_size);
			efivar_create_sysfs_entry(efivars,
						  variable_name_size,
						  variable_name, &vendor);
		}
	}
}