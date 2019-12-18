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
typedef  int /*<<< orphan*/  substring_t ;
struct super_block {int dummy; } ;
struct inode {int i_uid; int i_gid; int i_mode; } ;
struct TYPE_2__ {int debug; } ;

/* Variables and functions */
 int MAX_OPT_ARGS ; 
#define  Opt_debug 131 
#define  Opt_gid 130 
#define  Opt_mode 129 
#define  Opt_uid 128 
 int S_IFDIR ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_octal (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* spufs_get_sb_info (struct super_block*) ; 
 int /*<<< orphan*/  spufs_tokens ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
spufs_parse_options(struct super_block *sb, char *options, struct inode *root)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];

	while ((p = strsep(&options, ",")) != NULL) {
		int token, option;

		if (!*p)
			continue;

		token = match_token(p, spufs_tokens, args);
		switch (token) {
		case Opt_uid:
			if (match_int(&args[0], &option))
				return 0;
			root->i_uid = option;
			break;
		case Opt_gid:
			if (match_int(&args[0], &option))
				return 0;
			root->i_gid = option;
			break;
		case Opt_mode:
			if (match_octal(&args[0], &option))
				return 0;
			root->i_mode = option | S_IFDIR;
			break;
		case Opt_debug:
			spufs_get_sb_info(sb)->debug = 1;
			break;
		default:
			return 0;
		}
	}
	return 1;
}