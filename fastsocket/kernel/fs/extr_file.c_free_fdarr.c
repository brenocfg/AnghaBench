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
struct file {int dummy; } ;
struct fdtable {int max_fds; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void free_fdarr(struct fdtable *fdt)
{
	if (fdt->max_fds <= (PAGE_SIZE / sizeof(struct file *)))
		kfree(fdt->fd);
	else
		vfree(fdt->fd);
}