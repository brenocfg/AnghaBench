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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ get_safe_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_image () ; 
 int /*<<< orphan*/  resume_init_first_level_page_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resume_pg_dir ; 
 int resume_physical_mapping_init (int /*<<< orphan*/ *) ; 

int swsusp_arch_resume(void)
{
	int error;

	resume_pg_dir = (pgd_t *)get_safe_page(GFP_ATOMIC);
	if (!resume_pg_dir)
		return -ENOMEM;

	resume_init_first_level_page_table(resume_pg_dir);
	error = resume_physical_mapping_init(resume_pg_dir);
	if (error)
		return error;

	/* We have got enough memory and from now on we cannot recover */
	restore_image();
	return 0;
}