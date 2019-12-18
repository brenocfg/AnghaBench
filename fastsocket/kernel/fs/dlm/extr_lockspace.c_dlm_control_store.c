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
struct dlm_ls {int /*<<< orphan*/  ls_local_handle; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct dlm_ls* dlm_find_lockspace_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_ls_start (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_ls_stop (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t dlm_control_store(struct dlm_ls *ls, const char *buf, size_t len)
{
	ssize_t ret = len;
	int n = simple_strtol(buf, NULL, 0);

	ls = dlm_find_lockspace_local(ls->ls_local_handle);
	if (!ls)
		return -EINVAL;

	switch (n) {
	case 0:
		dlm_ls_stop(ls);
		break;
	case 1:
		dlm_ls_start(ls);
		break;
	default:
		ret = -EINVAL;
	}
	dlm_put_lockspace(ls);
	return ret;
}