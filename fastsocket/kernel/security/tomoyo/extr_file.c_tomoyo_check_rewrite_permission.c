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
typedef  int u8 ;
struct tomoyo_path_info {int dummy; } ;
struct tomoyo_domain_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt; } ;
struct file {TYPE_1__ f_path; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TOMOYO_MAC_FOR_FILE ; 
 int /*<<< orphan*/  TOMOYO_TYPE_REWRITE_ACL ; 
 int tomoyo_check_flags (struct tomoyo_domain_info*,int /*<<< orphan*/ ) ; 
 int tomoyo_check_single_path_permission2 (struct tomoyo_domain_info*,int /*<<< orphan*/ ,struct tomoyo_path_info*,int const) ; 
 int /*<<< orphan*/  tomoyo_free (struct tomoyo_path_info*) ; 
 struct tomoyo_path_info* tomoyo_get_path (TYPE_1__*) ; 
 int /*<<< orphan*/  tomoyo_is_no_rewrite_file (struct tomoyo_path_info*) ; 

int tomoyo_check_rewrite_permission(struct tomoyo_domain_info *domain,
				    struct file *filp)
{
	int error = -ENOMEM;
	const u8 mode = tomoyo_check_flags(domain, TOMOYO_MAC_FOR_FILE);
	const bool is_enforce = (mode == 3);
	struct tomoyo_path_info *buf;

	if (!mode || !filp->f_path.mnt)
		return 0;
	buf = tomoyo_get_path(&filp->f_path);
	if (!buf)
		goto out;
	if (!tomoyo_is_no_rewrite_file(buf)) {
		error = 0;
		goto out;
	}
	error = tomoyo_check_single_path_permission2(domain,
						     TOMOYO_TYPE_REWRITE_ACL,
						     buf, mode);
 out:
	tomoyo_free(buf);
	if (!is_enforce)
		error = 0;
	return error;
}