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
typedef  int u8 ;
struct tomoyo_path_info {scalar_t__ name; int /*<<< orphan*/  is_dir; } ;
struct tomoyo_domain_info {int dummy; } ;
struct path {int /*<<< orphan*/  mnt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TOMOYO_MAC_FOR_FILE ; 
#define  TOMOYO_TYPE_MKDIR_ACL 129 
#define  TOMOYO_TYPE_RMDIR_ACL 128 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int tomoyo_check_flags (struct tomoyo_domain_info*,int /*<<< orphan*/ ) ; 
 int tomoyo_check_single_path_permission2 (struct tomoyo_domain_info*,int const,struct tomoyo_path_info*,int const) ; 
 int /*<<< orphan*/  tomoyo_fill_path_info (struct tomoyo_path_info*) ; 
 int /*<<< orphan*/  tomoyo_free (struct tomoyo_path_info*) ; 
 struct tomoyo_path_info* tomoyo_get_path (struct path*) ; 

int tomoyo_check_1path_perm(struct tomoyo_domain_info *domain,
			    const u8 operation, struct path *path)
{
	int error = -ENOMEM;
	struct tomoyo_path_info *buf;
	const u8 mode = tomoyo_check_flags(domain, TOMOYO_MAC_FOR_FILE);
	const bool is_enforce = (mode == 3);

	if (!mode || !path->mnt)
		return 0;
	buf = tomoyo_get_path(path);
	if (!buf)
		goto out;
	switch (operation) {
	case TOMOYO_TYPE_MKDIR_ACL:
	case TOMOYO_TYPE_RMDIR_ACL:
		if (!buf->is_dir) {
			/*
			 * tomoyo_get_path() reserves space for appending "/."
			 */
			strcat((char *) buf->name, "/");
			tomoyo_fill_path_info(buf);
		}
	}
	error = tomoyo_check_single_path_permission2(domain, operation, buf,
						     mode);
 out:
	tomoyo_free(buf);
	if (!is_enforce)
		error = 0;
	return error;
}