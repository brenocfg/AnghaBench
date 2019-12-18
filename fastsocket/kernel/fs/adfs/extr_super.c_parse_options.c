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
struct super_block {int dummy; } ;
struct adfs_sb_info {int s_uid; int s_gid; int s_owner_mask; int s_other_mask; } ;

/* Variables and functions */
 struct adfs_sb_info* ADFS_SB (struct super_block*) ; 
 int EINVAL ; 
 int MAX_OPT_ARGS ; 
#define  Opt_gid 131 
#define  Opt_othmask 130 
#define  Opt_ownmask 129 
#define  Opt_uid 128 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_octal (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int parse_options(struct super_block *sb, char *options)
{
	char *p;
	struct adfs_sb_info *asb = ADFS_SB(sb);
	int option;

	if (!options)
		return 0;

	while ((p = strsep(&options, ",")) != NULL) {
		substring_t args[MAX_OPT_ARGS];
		int token;
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_uid:
			if (match_int(args, &option))
				return -EINVAL;
			asb->s_uid = option;
			break;
		case Opt_gid:
			if (match_int(args, &option))
				return -EINVAL;
			asb->s_gid = option;
			break;
		case Opt_ownmask:
			if (match_octal(args, &option))
				return -EINVAL;
			asb->s_owner_mask = option;
			break;
		case Opt_othmask:
			if (match_octal(args, &option))
				return -EINVAL;
			asb->s_other_mask = option;
			break;
		default:
			printk("ADFS-fs: unrecognised mount option \"%s\" "
					"or missing value\n", p);
			return -EINVAL;
		}
	}
	return 0;
}