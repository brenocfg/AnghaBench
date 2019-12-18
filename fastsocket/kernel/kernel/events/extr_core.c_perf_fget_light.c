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
struct file {int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 struct file* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct file* fget_light (int,int*) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 
 int /*<<< orphan*/  perf_fops ; 

__attribute__((used)) static struct file *perf_fget_light(int fd, int *fput_needed)
{
	struct file *file;

	file = fget_light(fd, fput_needed);
	if (!file)
		return ERR_PTR(-EBADF);

	if (file->f_op != &perf_fops) {
		fput_light(file, *fput_needed);
		*fput_needed = 0;
		return ERR_PTR(-EBADF);
	}

	return file;
}