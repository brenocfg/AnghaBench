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
typedef  int /*<<< orphan*/  substring_t ;
struct fuse_mount_data {int max_read; int blksize; int fd; int fd_present; int rootmode; int rootmode_present; int user_id; int user_id_present; int group_id; int group_id_present; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_ALLOW_OTHER ; 
 int FUSE_DEFAULT_BLKSIZE ; 
 int /*<<< orphan*/  FUSE_DEFAULT_PERMISSIONS ; 
 int MAX_OPT_ARGS ; 
#define  OPT_ALLOW_OTHER 135 
#define  OPT_BLKSIZE 134 
#define  OPT_DEFAULT_PERMISSIONS 133 
#define  OPT_FD 132 
#define  OPT_GROUP_ID 131 
#define  OPT_MAX_READ 130 
#define  OPT_ROOTMODE 129 
#define  OPT_USER_ID 128 
 int /*<<< orphan*/  fuse_valid_type (int) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_octal (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fuse_mount_data*,int /*<<< orphan*/ ,int) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int parse_fuse_opt(char *opt, struct fuse_mount_data *d, int is_bdev)
{
	char *p;
	memset(d, 0, sizeof(struct fuse_mount_data));
	d->max_read = ~0;
	d->blksize = FUSE_DEFAULT_BLKSIZE;

	while ((p = strsep(&opt, ",")) != NULL) {
		int token;
		int value;
		substring_t args[MAX_OPT_ARGS];
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case OPT_FD:
			if (match_int(&args[0], &value))
				return 0;
			d->fd = value;
			d->fd_present = 1;
			break;

		case OPT_ROOTMODE:
			if (match_octal(&args[0], &value))
				return 0;
			if (!fuse_valid_type(value))
				return 0;
			d->rootmode = value;
			d->rootmode_present = 1;
			break;

		case OPT_USER_ID:
			if (match_int(&args[0], &value))
				return 0;
			d->user_id = value;
			d->user_id_present = 1;
			break;

		case OPT_GROUP_ID:
			if (match_int(&args[0], &value))
				return 0;
			d->group_id = value;
			d->group_id_present = 1;
			break;

		case OPT_DEFAULT_PERMISSIONS:
			d->flags |= FUSE_DEFAULT_PERMISSIONS;
			break;

		case OPT_ALLOW_OTHER:
			d->flags |= FUSE_ALLOW_OTHER;
			break;

		case OPT_MAX_READ:
			if (match_int(&args[0], &value))
				return 0;
			d->max_read = value;
			break;

		case OPT_BLKSIZE:
			if (!is_bdev || match_int(&args[0], &value))
				return 0;
			d->blksize = value;
			break;

		default:
			return 0;
		}
	}

	if (!d->fd_present || !d->rootmode_present ||
	    !d->user_id_present || !d->group_id_present)
		return 0;

	return 1;
}