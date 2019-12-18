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
struct file {int /*<<< orphan*/  f_count; } ;

/* Variables and functions */
 scalar_t__ atomic_long_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_free (struct file*) ; 
 int /*<<< orphan*/  file_kill (struct file*) ; 
 int /*<<< orphan*/  security_file_free (struct file*) ; 

void put_filp(struct file *file)
{
	if (atomic_long_dec_and_test(&file->f_count)) {
		security_file_free(file);
		file_kill(file);
		file_free(file);
	}
}