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
struct TYPE_2__ {int unmount_mode; int bulk_read; int chk_data_crc; int override_compr; int /*<<< orphan*/  compr_type; } ;
struct ubifs_info {int bulk_read; int no_chk_data_crc; struct super_block* vfs_sb; TYPE_1__ mount_opts; int /*<<< orphan*/  default_compr; } ;
struct super_block {unsigned long s_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MAX_OPT_ARGS ; 
#define  Opt_bulk_read 134 
#define  Opt_chk_data_crc 133 
#define  Opt_fast_unmount 132 
#define  Opt_no_bulk_read 131 
#define  Opt_no_chk_data_crc 130 
#define  Opt_norm_unmount 129 
#define  Opt_override_compr 128 
 int /*<<< orphan*/  UBIFS_COMPR_LZO ; 
 int /*<<< orphan*/  UBIFS_COMPR_NONE ; 
 int /*<<< orphan*/  UBIFS_COMPR_ZLIB ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long parse_standard_option (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  ubifs_err (char*,char*) ; 

__attribute__((used)) static int ubifs_parse_options(struct ubifs_info *c, char *options,
			       int is_remount)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];

	if (!options)
		return 0;

	while ((p = strsep(&options, ","))) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		/*
		 * %Opt_fast_unmount and %Opt_norm_unmount options are ignored.
		 * We accept them in order to be backward-compatible. But this
		 * should be removed at some point.
		 */
		case Opt_fast_unmount:
			c->mount_opts.unmount_mode = 2;
			break;
		case Opt_norm_unmount:
			c->mount_opts.unmount_mode = 1;
			break;
		case Opt_bulk_read:
			c->mount_opts.bulk_read = 2;
			c->bulk_read = 1;
			break;
		case Opt_no_bulk_read:
			c->mount_opts.bulk_read = 1;
			c->bulk_read = 0;
			break;
		case Opt_chk_data_crc:
			c->mount_opts.chk_data_crc = 2;
			c->no_chk_data_crc = 0;
			break;
		case Opt_no_chk_data_crc:
			c->mount_opts.chk_data_crc = 1;
			c->no_chk_data_crc = 1;
			break;
		case Opt_override_compr:
		{
			char *name = match_strdup(&args[0]);

			if (!name)
				return -ENOMEM;
			if (!strcmp(name, "none"))
				c->mount_opts.compr_type = UBIFS_COMPR_NONE;
			else if (!strcmp(name, "lzo"))
				c->mount_opts.compr_type = UBIFS_COMPR_LZO;
			else if (!strcmp(name, "zlib"))
				c->mount_opts.compr_type = UBIFS_COMPR_ZLIB;
			else {
				ubifs_err("unknown compressor \"%s\"", name);
				kfree(name);
				return -EINVAL;
			}
			kfree(name);
			c->mount_opts.override_compr = 1;
			c->default_compr = c->mount_opts.compr_type;
			break;
		}
		default:
		{
			unsigned long flag;
			struct super_block *sb = c->vfs_sb;

			flag = parse_standard_option(p);
			if (!flag) {
				ubifs_err("unrecognized mount option \"%s\" "
					  "or missing value", p);
				return -EINVAL;
			}
			sb->s_flags |= flag;
			break;
		}
		}
	}

	return 0;
}