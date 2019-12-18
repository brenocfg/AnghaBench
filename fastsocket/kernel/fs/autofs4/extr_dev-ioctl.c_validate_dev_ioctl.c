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
struct autofs_dev_ioctl {int size; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_WARN (char*,int) ; 
 int check_dev_ioctl_version (int,struct autofs_dev_ioctl*) ; 
 int check_name (int /*<<< orphan*/ ) ; 
 int invalid_str (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int validate_dev_ioctl(int cmd, struct autofs_dev_ioctl *param)
{
	int err;

	err = check_dev_ioctl_version(cmd, param);
	if (err) {
		AUTOFS_WARN("invalid device control module version "
		     "supplied for cmd(0x%08x)", cmd);
		goto out;
	}

	if (param->size > sizeof(*param)) {
		err = invalid_str(param->path, param->size - sizeof(*param));
		if (err) {
			AUTOFS_WARN(
			  "path string terminator missing for cmd(0x%08x)",
			  cmd);
			goto out;
		}

		err = check_name(param->path);
		if (err) {
			AUTOFS_WARN("invalid path supplied for cmd(0x%08x)",
				    cmd);
			goto out;
		}
	}

	err = 0;
out:
	return err;
}