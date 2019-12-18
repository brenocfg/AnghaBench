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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  core_restore_code ; 
 scalar_t__ get_safe_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 void* relocated_restore_code ; 
 int /*<<< orphan*/  restore_image () ; 
 int /*<<< orphan*/  restore_registers ; 
 int set_up_temporary_mappings () ; 

int swsusp_arch_resume(void)
{
	int error;

	/* We have got enough memory and from now on we cannot recover */
	if ((error = set_up_temporary_mappings()))
		return error;

	relocated_restore_code = (void *)get_safe_page(GFP_ATOMIC);
	if (!relocated_restore_code)
		return -ENOMEM;
	memcpy(relocated_restore_code, &core_restore_code,
	       &restore_registers - &core_restore_code);

	restore_image();
	return 0;
}