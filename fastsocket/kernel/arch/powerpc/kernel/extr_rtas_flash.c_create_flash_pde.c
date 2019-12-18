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
struct proc_dir_entry {int dummy; } ;
struct file_operations {int dummy; } ;

/* Variables and functions */
 int S_IRUSR ; 
 int S_IWUSR ; 
 struct proc_dir_entry* proc_create (char const*,int,int /*<<< orphan*/ *,struct file_operations const*) ; 

__attribute__((used)) static struct proc_dir_entry *create_flash_pde(const char *filename,
					       const struct file_operations *fops)
{
	return proc_create(filename, S_IRUSR | S_IWUSR, NULL, fops);
}