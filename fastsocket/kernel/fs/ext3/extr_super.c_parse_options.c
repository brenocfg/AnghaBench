#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ from; scalar_t__ to; } ;
typedef  TYPE_1__ substring_t ;
struct super_block {int dummy; } ;
struct ext3_sb_info {int s_mount_opt; int s_resuid; int s_resgid; int s_commit_interval; char** s_qf_names; int s_jquota_fmt; } ;
typedef  int ext3_fsblk_t ;

/* Variables and functions */
 size_t ABORT ; 
 size_t BARRIER ; 
 size_t CHECK ; 
 size_t DATA_ERR_ABORT ; 
 size_t DEBUG ; 
 size_t ERRORS_CONT ; 
 size_t ERRORS_PANIC ; 
 size_t ERRORS_RO ; 
 int EXT3_MOUNT_DATA_FLAGS ; 
 int EXT3_MOUNT_GRPQUOTA ; 
 int EXT3_MOUNT_JOURNAL_DATA ; 
 int EXT3_MOUNT_ORDERED_DATA ; 
 int EXT3_MOUNT_USRQUOTA ; 
 int EXT3_MOUNT_WRITEBACK_DATA ; 
 struct ext3_sb_info* EXT3_SB (struct super_block*) ; 
 size_t GRPID ; 
 size_t GRPQUOTA ; 
 int HZ ; 
 int JBD_DEFAULT_MAX_COMMIT_AGE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MAX_OPT_ARGS ; 
 size_t MINIX_DF ; 
 size_t NOBH ; 
 size_t NOLOAD ; 
 size_t NO_UID32 ; 
 size_t OLDALLOC ; 
#define  Opt_abort 176 
#define  Opt_acl 175 
#define  Opt_barrier 174 
#define  Opt_bh 173 
#define  Opt_bsd_df 172 
#define  Opt_commit 171 
#define  Opt_data_err_abort 170 
#define  Opt_data_err_ignore 169 
#define  Opt_data_journal 168 
#define  Opt_data_ordered 167 
#define  Opt_data_writeback 166 
#define  Opt_debug 165 
#define  Opt_err_cont 164 
#define  Opt_err_panic 163 
#define  Opt_err_ro 162 
#define  Opt_grpid 161 
#define  Opt_grpjquota 160 
#define  Opt_grpquota 159 
#define  Opt_ignore 158 
#define  Opt_journal_dev 157 
#define  Opt_journal_inum 156 
#define  Opt_journal_update 155 
#define  Opt_jqfmt_vfsold 154 
#define  Opt_jqfmt_vfsv0 153 
#define  Opt_jqfmt_vfsv1 152 
#define  Opt_minix_df 151 
#define  Opt_noacl 150 
#define  Opt_nobarrier 149 
#define  Opt_nobh 148 
#define  Opt_nocheck 147 
#define  Opt_nogrpid 146 
#define  Opt_noload 145 
#define  Opt_noquota 144 
#define  Opt_noreservation 143 
#define  Opt_nouid32 142 
#define  Opt_nouser_xattr 141 
#define  Opt_offgrpjquota 140 
#define  Opt_offusrjquota 139 
#define  Opt_oldalloc 138 
#define  Opt_orlov 137 
#define  Opt_quota 136 
#define  Opt_reservation 135 
#define  Opt_resgid 134 
#define  Opt_resize 133 
#define  Opt_resuid 132 
#define  Opt_sb 131 
#define  Opt_user_xattr 130 
#define  Opt_usrjquota 129 
#define  Opt_usrquota 128 
 size_t POSIX_ACL ; 
 int QFMT_VFS_OLD ; 
 int QFMT_VFS_V0 ; 
 int QFMT_VFS_V1 ; 
 int /*<<< orphan*/  QTYPE2NAME (int) ; 
 size_t QUOTA ; 
 size_t RESERVATION ; 
 size_t UPDATE_JOURNAL ; 
 size_t USRQUOTA ; 
 size_t XATTR_USER ; 
 int /*<<< orphan*/  clear_opt (int,size_t) ; 
 int /*<<< orphan*/  data_mode_string (int) ; 
 int /*<<< orphan*/  ext3_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  match_int (TYPE_1__*,int*) ; 
 char* match_strdup (TYPE_1__*) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sb_any_quota_loaded (struct super_block*) ; 
 int /*<<< orphan*/  set_opt (int,size_t) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int parse_options (char *options, struct super_block *sb,
			  unsigned int *inum, unsigned long *journal_devnum,
			  ext3_fsblk_t *n_blocks_count, int is_remount)
{
	struct ext3_sb_info *sbi = EXT3_SB(sb);
	char * p;
	substring_t args[MAX_OPT_ARGS];
	int data_opt = 0;
	int option;
#ifdef CONFIG_QUOTA
	int qtype, qfmt;
	char *qname;
#endif

	if (!options)
		return 1;

	while ((p = strsep (&options, ",")) != NULL) {
		int token;
		if (!*p)
			continue;
		/*
		 * Initialize args struct so we know whether arg was
		 * found; some options take optional arguments.
		 */
		args[0].to = args[0].from = 0;
		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_bsd_df:
			clear_opt (sbi->s_mount_opt, MINIX_DF);
			break;
		case Opt_minix_df:
			set_opt (sbi->s_mount_opt, MINIX_DF);
			break;
		case Opt_grpid:
			set_opt (sbi->s_mount_opt, GRPID);
			break;
		case Opt_nogrpid:
			clear_opt (sbi->s_mount_opt, GRPID);
			break;
		case Opt_resuid:
			if (match_int(&args[0], &option))
				return 0;
			sbi->s_resuid = option;
			break;
		case Opt_resgid:
			if (match_int(&args[0], &option))
				return 0;
			sbi->s_resgid = option;
			break;
		case Opt_sb:
			/* handled by get_sb_block() instead of here */
			/* *sb_block = match_int(&args[0]); */
			break;
		case Opt_err_panic:
			clear_opt (sbi->s_mount_opt, ERRORS_CONT);
			clear_opt (sbi->s_mount_opt, ERRORS_RO);
			set_opt (sbi->s_mount_opt, ERRORS_PANIC);
			break;
		case Opt_err_ro:
			clear_opt (sbi->s_mount_opt, ERRORS_CONT);
			clear_opt (sbi->s_mount_opt, ERRORS_PANIC);
			set_opt (sbi->s_mount_opt, ERRORS_RO);
			break;
		case Opt_err_cont:
			clear_opt (sbi->s_mount_opt, ERRORS_RO);
			clear_opt (sbi->s_mount_opt, ERRORS_PANIC);
			set_opt (sbi->s_mount_opt, ERRORS_CONT);
			break;
		case Opt_nouid32:
			set_opt (sbi->s_mount_opt, NO_UID32);
			break;
		case Opt_nocheck:
			clear_opt (sbi->s_mount_opt, CHECK);
			break;
		case Opt_debug:
			set_opt (sbi->s_mount_opt, DEBUG);
			break;
		case Opt_oldalloc:
			set_opt (sbi->s_mount_opt, OLDALLOC);
			break;
		case Opt_orlov:
			clear_opt (sbi->s_mount_opt, OLDALLOC);
			break;
#ifdef CONFIG_EXT3_FS_XATTR
		case Opt_user_xattr:
			set_opt (sbi->s_mount_opt, XATTR_USER);
			break;
		case Opt_nouser_xattr:
			clear_opt (sbi->s_mount_opt, XATTR_USER);
			break;
#else
		case Opt_user_xattr:
		case Opt_nouser_xattr:
			ext3_msg(sb, KERN_INFO,
				"(no)user_xattr options not supported");
			break;
#endif
#ifdef CONFIG_EXT3_FS_POSIX_ACL
		case Opt_acl:
			set_opt(sbi->s_mount_opt, POSIX_ACL);
			break;
		case Opt_noacl:
			clear_opt(sbi->s_mount_opt, POSIX_ACL);
			break;
#else
		case Opt_acl:
		case Opt_noacl:
			ext3_msg(sb, KERN_INFO,
				"(no)acl options not supported");
			break;
#endif
		case Opt_reservation:
			set_opt(sbi->s_mount_opt, RESERVATION);
			break;
		case Opt_noreservation:
			clear_opt(sbi->s_mount_opt, RESERVATION);
			break;
		case Opt_journal_update:
			/* @@@ FIXME */
			/* Eventually we will want to be able to create
			   a journal file here.  For now, only allow the
			   user to specify an existing inode to be the
			   journal file. */
			if (is_remount) {
				ext3_msg(sb, KERN_ERR, "error: cannot specify "
					"journal on remount");
				return 0;
			}
			set_opt (sbi->s_mount_opt, UPDATE_JOURNAL);
			break;
		case Opt_journal_inum:
			if (is_remount) {
				ext3_msg(sb, KERN_ERR, "error: cannot specify "
				       "journal on remount");
				return 0;
			}
			if (match_int(&args[0], &option))
				return 0;
			*inum = option;
			break;
		case Opt_journal_dev:
			if (is_remount) {
				ext3_msg(sb, KERN_ERR, "error: cannot specify "
				       "journal on remount");
				return 0;
			}
			if (match_int(&args[0], &option))
				return 0;
			*journal_devnum = option;
			break;
		case Opt_noload:
			set_opt (sbi->s_mount_opt, NOLOAD);
			break;
		case Opt_commit:
			if (match_int(&args[0], &option))
				return 0;
			if (option < 0)
				return 0;
			if (option == 0)
				option = JBD_DEFAULT_MAX_COMMIT_AGE;
			sbi->s_commit_interval = HZ * option;
			break;
		case Opt_data_journal:
			data_opt = EXT3_MOUNT_JOURNAL_DATA;
			goto datacheck;
		case Opt_data_ordered:
			data_opt = EXT3_MOUNT_ORDERED_DATA;
			goto datacheck;
		case Opt_data_writeback:
			data_opt = EXT3_MOUNT_WRITEBACK_DATA;
		datacheck:
			if (is_remount) {
				if ((sbi->s_mount_opt & EXT3_MOUNT_DATA_FLAGS)
						== data_opt)
					break;
				ext3_msg(sb, KERN_ERR,
					"error: cannot change "
					"data mode on remount. The filesystem "
					"is mounted in data=%s mode and you "
					"try to remount it in data=%s mode.",
					data_mode_string(sbi->s_mount_opt &
							EXT3_MOUNT_DATA_FLAGS),
					data_mode_string(data_opt));
				return 0;
			} else {
				sbi->s_mount_opt &= ~EXT3_MOUNT_DATA_FLAGS;
				sbi->s_mount_opt |= data_opt;
			}
			break;
		case Opt_data_err_abort:
			set_opt(sbi->s_mount_opt, DATA_ERR_ABORT);
			break;
		case Opt_data_err_ignore:
			clear_opt(sbi->s_mount_opt, DATA_ERR_ABORT);
			break;
#ifdef CONFIG_QUOTA
		case Opt_usrjquota:
			qtype = USRQUOTA;
			goto set_qf_name;
		case Opt_grpjquota:
			qtype = GRPQUOTA;
set_qf_name:
			if (sb_any_quota_loaded(sb) &&
			    !sbi->s_qf_names[qtype]) {
				ext3_msg(sb, KERN_ERR,
					"error: cannot change journaled "
					"quota options when quota turned on.");
				return 0;
			}
			qname = match_strdup(&args[0]);
			if (!qname) {
				ext3_msg(sb, KERN_ERR,
					"error: not enough memory for "
					"storing quotafile name.");
				return 0;
			}
			if (sbi->s_qf_names[qtype] &&
			    strcmp(sbi->s_qf_names[qtype], qname)) {
				ext3_msg(sb, KERN_ERR,
					"error: %s quota file already "
					"specified.", QTYPE2NAME(qtype));
				kfree(qname);
				return 0;
			}
			sbi->s_qf_names[qtype] = qname;
			if (strchr(sbi->s_qf_names[qtype], '/')) {
				ext3_msg(sb, KERN_ERR,
					"error: quotafile must be on "
					"filesystem root.");
				kfree(sbi->s_qf_names[qtype]);
				sbi->s_qf_names[qtype] = NULL;
				return 0;
			}
			set_opt(sbi->s_mount_opt, QUOTA);
			break;
		case Opt_offusrjquota:
			qtype = USRQUOTA;
			goto clear_qf_name;
		case Opt_offgrpjquota:
			qtype = GRPQUOTA;
clear_qf_name:
			if (sb_any_quota_loaded(sb) &&
			    sbi->s_qf_names[qtype]) {
				ext3_msg(sb, KERN_ERR, "error: cannot change "
					"journaled quota options when "
					"quota turned on.");
				return 0;
			}
			/*
			 * The space will be released later when all options
			 * are confirmed to be correct
			 */
			sbi->s_qf_names[qtype] = NULL;
			break;
		case Opt_jqfmt_vfsold:
			qfmt = QFMT_VFS_OLD;
			goto set_qf_format;
		case Opt_jqfmt_vfsv0:
			qfmt = QFMT_VFS_V0;
			goto set_qf_format;
		case Opt_jqfmt_vfsv1:
			qfmt = QFMT_VFS_V1;
set_qf_format:
			if (sb_any_quota_loaded(sb) &&
			    sbi->s_jquota_fmt != qfmt) {
				ext3_msg(sb, KERN_ERR, "error: cannot change "
					"journaled quota options when "
					"quota turned on.");
				return 0;
			}
			sbi->s_jquota_fmt = qfmt;
			break;
		case Opt_quota:
		case Opt_usrquota:
			set_opt(sbi->s_mount_opt, QUOTA);
			set_opt(sbi->s_mount_opt, USRQUOTA);
			break;
		case Opt_grpquota:
			set_opt(sbi->s_mount_opt, QUOTA);
			set_opt(sbi->s_mount_opt, GRPQUOTA);
			break;
		case Opt_noquota:
			if (sb_any_quota_loaded(sb)) {
				ext3_msg(sb, KERN_ERR, "error: cannot change "
					"quota options when quota turned on.");
				return 0;
			}
			clear_opt(sbi->s_mount_opt, QUOTA);
			clear_opt(sbi->s_mount_opt, USRQUOTA);
			clear_opt(sbi->s_mount_opt, GRPQUOTA);
			break;
#else
		case Opt_quota:
		case Opt_usrquota:
		case Opt_grpquota:
			ext3_msg(sb, KERN_ERR,
				"error: quota options not supported.");
			break;
		case Opt_usrjquota:
		case Opt_grpjquota:
		case Opt_offusrjquota:
		case Opt_offgrpjquota:
		case Opt_jqfmt_vfsold:
		case Opt_jqfmt_vfsv0:
		case Opt_jqfmt_vfsv1:
			ext3_msg(sb, KERN_ERR,
				"error: journaled quota options not "
				"supported.");
			break;
		case Opt_noquota:
			break;
#endif
		case Opt_abort:
			set_opt(sbi->s_mount_opt, ABORT);
			break;
		case Opt_nobarrier:
			clear_opt(sbi->s_mount_opt, BARRIER);
			break;
		case Opt_barrier:
			if (args[0].from) {
				if (match_int(&args[0], &option))
					return 0;
			} else
				option = 1;	/* No argument, default to 1 */
			if (option)
				set_opt(sbi->s_mount_opt, BARRIER);
			else
				clear_opt(sbi->s_mount_opt, BARRIER);
			break;
		case Opt_ignore:
			break;
		case Opt_resize:
			if (!is_remount) {
				ext3_msg(sb, KERN_ERR,
					"error: resize option only available "
					"for remount");
				return 0;
			}
			if (match_int(&args[0], &option) != 0)
				return 0;
			*n_blocks_count = option;
			break;
		case Opt_nobh:
			set_opt(sbi->s_mount_opt, NOBH);
			break;
		case Opt_bh:
			clear_opt(sbi->s_mount_opt, NOBH);
			break;
		default:
			ext3_msg(sb, KERN_ERR,
				"error: unrecognized mount option \"%s\" "
				"or missing value", p);
			return 0;
		}
	}
#ifdef CONFIG_QUOTA
	if (sbi->s_qf_names[USRQUOTA] || sbi->s_qf_names[GRPQUOTA]) {
		if ((sbi->s_mount_opt & EXT3_MOUNT_USRQUOTA) &&
		     sbi->s_qf_names[USRQUOTA])
			clear_opt(sbi->s_mount_opt, USRQUOTA);

		if ((sbi->s_mount_opt & EXT3_MOUNT_GRPQUOTA) &&
		     sbi->s_qf_names[GRPQUOTA])
			clear_opt(sbi->s_mount_opt, GRPQUOTA);

		if ((sbi->s_qf_names[USRQUOTA] &&
				(sbi->s_mount_opt & EXT3_MOUNT_GRPQUOTA)) ||
		    (sbi->s_qf_names[GRPQUOTA] &&
				(sbi->s_mount_opt & EXT3_MOUNT_USRQUOTA))) {
			ext3_msg(sb, KERN_ERR, "error: old and new quota "
					"format mixing.");
			return 0;
		}

		if (!sbi->s_jquota_fmt) {
			ext3_msg(sb, KERN_ERR, "error: journaled quota format "
					"not specified.");
			return 0;
		}
	} else {
		if (sbi->s_jquota_fmt) {
			ext3_msg(sb, KERN_ERR, "error: journaled quota format "
					"specified with no journaling "
					"enabled.");
			return 0;
		}
	}
#endif
	return 1;
}