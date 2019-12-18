#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {unsigned long s_blocksize_bits; TYPE_2__* s_bdev; } ;
struct TYPE_8__ {char* member_0; char arg_required; int clrmask; int setmask; char* option_name; int /*<<< orphan*/ * values; } ;
typedef  TYPE_3__ opt_desc_t ;
struct TYPE_9__ {char** s_qf_names; unsigned int s_jquota_fmt; } ;
struct TYPE_7__ {TYPE_1__* bd_inode; } ;
struct TYPE_6__ {unsigned long i_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t GRPQUOTA ; 
 unsigned int QFMT_VFS_OLD ; 
 unsigned int QFMT_VFS_V0 ; 
 int /*<<< orphan*/  QTYPE2NAME (int) ; 
 int REISERFS_ATTRS ; 
 int REISERFS_CONVERT ; 
 int REISERFS_EXPOSE_PRIVROOT ; 
 int REISERFS_LARGETAIL ; 
 int REISERFS_OPT_ALLOWEMPTY ; 
 int REISERFS_POSIXACL ; 
 int REISERFS_QUOTA ; 
 TYPE_5__* REISERFS_SB (struct super_block*) ; 
 int REISERFS_SMALLTAIL ; 
 int REISERFS_UNSUPPORTED_OPT ; 
 int REISERFS_XATTRS_USER ; 
 int REPLAYONLY ; 
 size_t USRQUOTA ; 
 int /*<<< orphan*/ * balloc ; 
 int /*<<< orphan*/ * barrier_mode ; 
 int /*<<< orphan*/ * error_actions ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * logging_mode ; 
 int reiserfs_getopt (struct super_block*,char**,TYPE_3__*,char**,unsigned long*) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,...) ; 
 scalar_t__ sb_any_quota_loaded (struct super_block*) ; 
 unsigned long simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/ * tails ; 

__attribute__((used)) static int reiserfs_parse_options(struct super_block *s, char *options,	/* string given via mount's -o */
				  unsigned long *mount_options,
				  /* after the parsing phase, contains the
				     collection of bitflags defining what
				     mount options were selected. */
				  unsigned long *blocks,	/* strtol-ed from NNN of resize=NNN */
				  char **jdev_name,
				  unsigned int *commit_max_age,
				  char **qf_names,
				  unsigned int *qfmt)
{
	int c;
	char *arg = NULL;
	char *pos;
	opt_desc_t opts[] = {
		/* Compatibility stuff, so that -o notail for old setups still work */
		{"tails",.arg_required = 't',.values = tails},
		{"notail",.clrmask =
		 (1 << REISERFS_LARGETAIL) | (1 << REISERFS_SMALLTAIL)},
		{"conv",.setmask = 1 << REISERFS_CONVERT},
		{"attrs",.setmask = 1 << REISERFS_ATTRS},
		{"noattrs",.clrmask = 1 << REISERFS_ATTRS},
		{"expose_privroot", .setmask = 1 << REISERFS_EXPOSE_PRIVROOT},
#ifdef CONFIG_REISERFS_FS_XATTR
		{"user_xattr",.setmask = 1 << REISERFS_XATTRS_USER},
		{"nouser_xattr",.clrmask = 1 << REISERFS_XATTRS_USER},
#else
		{"user_xattr",.setmask = 1 << REISERFS_UNSUPPORTED_OPT},
		{"nouser_xattr",.clrmask = 1 << REISERFS_UNSUPPORTED_OPT},
#endif
#ifdef CONFIG_REISERFS_FS_POSIX_ACL
		{"acl",.setmask = 1 << REISERFS_POSIXACL},
		{"noacl",.clrmask = 1 << REISERFS_POSIXACL},
#else
		{"acl",.setmask = 1 << REISERFS_UNSUPPORTED_OPT},
		{"noacl",.clrmask = 1 << REISERFS_UNSUPPORTED_OPT},
#endif
		{.option_name = "nolog"},
		{"replayonly",.setmask = 1 << REPLAYONLY},
		{"block-allocator",.arg_required = 'a',.values = balloc},
		{"data",.arg_required = 'd',.values = logging_mode},
		{"barrier",.arg_required = 'b',.values = barrier_mode},
		{"resize",.arg_required = 'r',.values = NULL},
		{"jdev",.arg_required = 'j',.values = NULL},
		{"nolargeio",.arg_required = 'w',.values = NULL},
		{"commit",.arg_required = 'c',.values = NULL},
		{"usrquota",.setmask = 1 << REISERFS_QUOTA},
		{"grpquota",.setmask = 1 << REISERFS_QUOTA},
		{"noquota",.clrmask = 1 << REISERFS_QUOTA},
		{"errors",.arg_required = 'e',.values = error_actions},
		{"usrjquota",.arg_required =
		 'u' | (1 << REISERFS_OPT_ALLOWEMPTY),.values = NULL},
		{"grpjquota",.arg_required =
		 'g' | (1 << REISERFS_OPT_ALLOWEMPTY),.values = NULL},
		{"jqfmt",.arg_required = 'f',.values = NULL},
		{.option_name = NULL}
	};

	*blocks = 0;
	if (!options || !*options)
		/* use default configuration: create tails, journaling on, no
		   conversion to newest format */
		return 1;

	for (pos = options; pos;) {
		c = reiserfs_getopt(s, &pos, opts, &arg, mount_options);
		if (c == -1)
			/* wrong option is given */
			return 0;

		if (c == 'r') {
			char *p;

			p = NULL;
			/* "resize=NNN" or "resize=auto" */

			if (!strcmp(arg, "auto")) {
				/* From JFS code, to auto-get the size. */
				*blocks =
				    s->s_bdev->bd_inode->i_size >> s->
				    s_blocksize_bits;
			} else {
				*blocks = simple_strtoul(arg, &p, 0);
				if (*p != '\0') {
					/* NNN does not look like a number */
					reiserfs_warning(s, "super-6507",
							 "bad value %s for "
							 "-oresize\n", arg);
					return 0;
				}
			}
		}

		if (c == 'c') {
			char *p = NULL;
			unsigned long val = simple_strtoul(arg, &p, 0);
			/* commit=NNN (time in seconds) */
			if (*p != '\0' || val >= (unsigned int)-1) {
				reiserfs_warning(s, "super-6508",
						 "bad value %s for -ocommit\n",
						 arg);
				return 0;
			}
			*commit_max_age = (unsigned int)val;
		}

		if (c == 'w') {
			reiserfs_warning(s, "super-6509", "nolargeio option "
					 "is no longer supported");
			return 0;
		}

		if (c == 'j') {
			if (arg && *arg && jdev_name) {
				if (*jdev_name) {	//Hm, already assigned?
					reiserfs_warning(s, "super-6510",
							 "journal device was "
							 "already specified to "
							 "be %s", *jdev_name);
					return 0;
				}
				*jdev_name = arg;
			}
		}
#ifdef CONFIG_QUOTA
		if (c == 'u' || c == 'g') {
			int qtype = c == 'u' ? USRQUOTA : GRPQUOTA;

			if (sb_any_quota_loaded(s) &&
			    (!*arg != !REISERFS_SB(s)->s_qf_names[qtype])) {
				reiserfs_warning(s, "super-6511",
						 "cannot change journaled "
						 "quota options when quota "
						 "turned on.");
				return 0;
			}
			if (*arg) {	/* Some filename specified? */
				if (REISERFS_SB(s)->s_qf_names[qtype]
				    && strcmp(REISERFS_SB(s)->s_qf_names[qtype],
					      arg)) {
					reiserfs_warning(s, "super-6512",
							 "%s quota file "
							 "already specified.",
							 QTYPE2NAME(qtype));
					return 0;
				}
				if (strchr(arg, '/')) {
					reiserfs_warning(s, "super-6513",
							 "quotafile must be "
							 "on filesystem root.");
					return 0;
				}
				qf_names[qtype] =
				    kmalloc(strlen(arg) + 1, GFP_KERNEL);
				if (!qf_names[qtype]) {
					reiserfs_warning(s, "reiserfs-2502",
							 "not enough memory "
							 "for storing "
							 "quotafile name.");
					return 0;
				}
				strcpy(qf_names[qtype], arg);
				*mount_options |= 1 << REISERFS_QUOTA;
			} else {
				if (qf_names[qtype] !=
				    REISERFS_SB(s)->s_qf_names[qtype])
					kfree(qf_names[qtype]);
				qf_names[qtype] = NULL;
			}
		}
		if (c == 'f') {
			if (!strcmp(arg, "vfsold"))
				*qfmt = QFMT_VFS_OLD;
			else if (!strcmp(arg, "vfsv0"))
				*qfmt = QFMT_VFS_V0;
			else {
				reiserfs_warning(s, "super-6514",
						 "unknown quota format "
						 "specified.");
				return 0;
			}
			if (sb_any_quota_loaded(s) &&
			    *qfmt != REISERFS_SB(s)->s_jquota_fmt) {
				reiserfs_warning(s, "super-6515",
						 "cannot change journaled "
						 "quota options when quota "
						 "turned on.");
				return 0;
			}
		}
#else
		if (c == 'u' || c == 'g' || c == 'f') {
			reiserfs_warning(s, "reiserfs-2503", "journaled "
					 "quota options not supported.");
			return 0;
		}
#endif
	}

#ifdef CONFIG_QUOTA
	if (!REISERFS_SB(s)->s_jquota_fmt && !*qfmt
	    && (qf_names[USRQUOTA] || qf_names[GRPQUOTA])) {
		reiserfs_warning(s, "super-6515",
				 "journaled quota format not specified.");
		return 0;
	}
	/* This checking is not precise wrt the quota type but for our purposes it is sufficient */
	if (!(*mount_options & (1 << REISERFS_QUOTA))
	    && sb_any_quota_loaded(s)) {
		reiserfs_warning(s, "super-6516", "quota options must "
				 "be present when quota is turned on.");
		return 0;
	}
#endif

	return 1;
}