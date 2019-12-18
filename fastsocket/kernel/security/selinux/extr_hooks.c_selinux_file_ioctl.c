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
typedef  int /*<<< orphan*/  u32 ;
struct file {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE__IOCTL ; 
 int /*<<< orphan*/  FILE__READ ; 
 int /*<<< orphan*/  FILE__WRITE ; 
 int _IOC_DIR (unsigned int) ; 
 int _IOC_READ ; 
 int _IOC_WRITE ; 
 struct cred* current_cred () ; 
 int file_has_perm (struct cred const*,struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_file_ioctl(struct file *file, unsigned int cmd,
			      unsigned long arg)
{
	const struct cred *cred = current_cred();
	u32 av = 0;

	if (_IOC_DIR(cmd) & _IOC_WRITE)
		av |= FILE__WRITE;
	if (_IOC_DIR(cmd) & _IOC_READ)
		av |= FILE__READ;
	if (!av)
		av = FILE__IOCTL;

	return file_has_perm(cred, file, av);
}