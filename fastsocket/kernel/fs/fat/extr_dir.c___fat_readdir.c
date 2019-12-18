#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct super_block {int dummy; } ;
struct nls_table {int dummy; } ;
struct TYPE_4__ {unsigned short shortname; int isvfat; int nocase; scalar_t__ dotsOK; } ;
struct msdos_sb_info {TYPE_2__ options; struct nls_table* nls_disk; } ;
struct msdos_dir_entry {scalar_t__* name; int attr; int lcase; } ;
struct inode {unsigned long i_ino; struct super_block* i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  dentry; } ;
struct file {int f_pos; TYPE_1__ f_path; } ;
struct fat_ioctl_filldir_callback {char const* longname; int long_len; unsigned char* shortname; int short_len; } ;
struct buffer_head {int dummy; } ;
typedef  int loff_t ;
typedef  scalar_t__ (* filldir_t ) (void*,char const*,int,unsigned long,unsigned long,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  bufname ;

/* Variables and functions */
 int ATTR_DIR ; 
 int ATTR_EXT ; 
 int ATTR_HIDDEN ; 
 int ATTR_VOLUME ; 
 int CASE_LOWER_BASE ; 
 int CASE_LOWER_EXT ; 
 scalar_t__ DELETED_FLAG ; 
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_REG ; 
 int ENOENT ; 
 int FAT_MAX_SHORT_SIZE ; 
 int FAT_MAX_UNI_CHARS ; 
 int FAT_MAX_UNI_SIZE ; 
 scalar_t__ IS_FREE (scalar_t__*) ; 
 int /*<<< orphan*/  MSDOS_DOT ; 
 int /*<<< orphan*/  MSDOS_DOTDOT ; 
 int MSDOS_NAME ; 
 unsigned long MSDOS_ROOT_INO ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int PARSE_EOF ; 
 int PARSE_INVALID ; 
 int PARSE_NOT_LONGNAME ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  __putname (int*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int fat_get_entry (struct inode*,int*,struct buffer_head**,struct msdos_dir_entry**) ; 
 struct inode* fat_iget (struct super_block*,int) ; 
 int fat_make_i_pos (struct super_block*,struct buffer_head*,struct msdos_dir_entry*) ; 
 int fat_parse_long (struct inode*,int*,struct buffer_head**,struct msdos_dir_entry**,int**,unsigned char*) ; 
 int /*<<< orphan*/  fat_short2uni (struct nls_table*,char*,int,int*) ; 
 int fat_shortname2uni (struct nls_table*,unsigned char*,int,int*,unsigned short,int) ; 
 int fat_uni_to_x8 (struct msdos_sb_info*,int*,unsigned char*,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 unsigned long iunique (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  memcmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__*,int) ; 
 unsigned long parent_ino (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static int __fat_readdir(struct inode *inode, struct file *filp, void *dirent,
			 filldir_t filldir, int short_only, int both)
{
	struct super_block *sb = inode->i_sb;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	struct buffer_head *bh;
	struct msdos_dir_entry *de;
	struct nls_table *nls_disk = sbi->nls_disk;
	unsigned char nr_slots;
	wchar_t bufuname[14];
	wchar_t *unicode = NULL;
	unsigned char c, work[MSDOS_NAME];
	unsigned char bufname[FAT_MAX_SHORT_SIZE], *ptname = bufname;
	unsigned short opt_shortname = sbi->options.shortname;
	int isvfat = sbi->options.isvfat;
	int nocase = sbi->options.nocase;
	const char *fill_name = NULL;
	unsigned long inum;
	unsigned long lpos, dummy, *furrfu = &lpos;
	loff_t cpos;
	int chi, chl, i, i2, j, last, last_u, dotoffset = 0, fill_len = 0;
	int ret = 0;

	lock_super(sb);

	cpos = filp->f_pos;
	/* Fake . and .. for the root directory. */
	if (inode->i_ino == MSDOS_ROOT_INO) {
		while (cpos < 2) {
			if (filldir(dirent, "..", cpos+1, cpos, MSDOS_ROOT_INO, DT_DIR) < 0)
				goto out;
			cpos++;
			filp->f_pos++;
		}
		if (cpos == 2) {
			dummy = 2;
			furrfu = &dummy;
			cpos = 0;
		}
	}
	if (cpos & (sizeof(struct msdos_dir_entry) - 1)) {
		ret = -ENOENT;
		goto out;
	}

	bh = NULL;
get_new:
	if (fat_get_entry(inode, &cpos, &bh, &de) == -1)
		goto end_of_dir;
parse_record:
	nr_slots = 0;
	/*
	 * Check for long filename entry, but if short_only, we don't
	 * need to parse long filename.
	 */
	if (isvfat && !short_only) {
		if (de->name[0] == DELETED_FLAG)
			goto record_end;
		if (de->attr != ATTR_EXT && (de->attr & ATTR_VOLUME))
			goto record_end;
		if (de->attr != ATTR_EXT && IS_FREE(de->name))
			goto record_end;
	} else {
		if ((de->attr & ATTR_VOLUME) || IS_FREE(de->name))
			goto record_end;
	}

	if (isvfat && de->attr == ATTR_EXT) {
		int status = fat_parse_long(inode, &cpos, &bh, &de,
					    &unicode, &nr_slots);
		if (status < 0) {
			filp->f_pos = cpos;
			ret = status;
			goto out;
		} else if (status == PARSE_INVALID)
			goto record_end;
		else if (status == PARSE_NOT_LONGNAME)
			goto parse_record;
		else if (status == PARSE_EOF)
			goto end_of_dir;

		if (nr_slots) {
			void *longname = unicode + FAT_MAX_UNI_CHARS;
			int size = PATH_MAX - FAT_MAX_UNI_SIZE;
			int len = fat_uni_to_x8(sbi, unicode, longname, size);

			fill_name = longname;
			fill_len = len;
			/* !both && !short_only, so we don't need shortname. */
			if (!both)
				goto start_filldir;
		}
	}

	if (sbi->options.dotsOK) {
		ptname = bufname;
		dotoffset = 0;
		if (de->attr & ATTR_HIDDEN) {
			*ptname++ = '.';
			dotoffset = 1;
		}
	}

	memcpy(work, de->name, sizeof(de->name));
	/* see namei.c, msdos_format_name */
	if (work[0] == 0x05)
		work[0] = 0xE5;
	for (i = 0, j = 0, last = 0, last_u = 0; i < 8;) {
		if (!(c = work[i]))
			break;
		chl = fat_shortname2uni(nls_disk, &work[i], 8 - i,
					&bufuname[j++], opt_shortname,
					de->lcase & CASE_LOWER_BASE);
		if (chl <= 1) {
			ptname[i++] = (!nocase && c>='A' && c<='Z') ? c+32 : c;
			if (c != ' ') {
				last = i;
				last_u = j;
			}
		} else {
			last_u = j;
			for (chi = 0; chi < chl && i < 8; chi++) {
				ptname[i] = work[i];
				i++; last = i;
			}
		}
	}
	i = last;
	j = last_u;
	fat_short2uni(nls_disk, ".", 1, &bufuname[j++]);
	ptname[i++] = '.';
	for (i2 = 8; i2 < MSDOS_NAME;) {
		if (!(c = work[i2]))
			break;
		chl = fat_shortname2uni(nls_disk, &work[i2], MSDOS_NAME - i2,
					&bufuname[j++], opt_shortname,
					de->lcase & CASE_LOWER_EXT);
		if (chl <= 1) {
			i2++;
			ptname[i++] = (!nocase && c>='A' && c<='Z') ? c+32 : c;
			if (c != ' ') {
				last = i;
				last_u = j;
			}
		} else {
			last_u = j;
			for (chi = 0; chi < chl && i2 < MSDOS_NAME; chi++) {
				ptname[i++] = work[i2++];
				last = i;
			}
		}
	}
	if (!last)
		goto record_end;

	i = last + dotoffset;
	j = last_u;

	if (isvfat) {
		bufuname[j] = 0x0000;
		i = fat_uni_to_x8(sbi, bufuname, bufname, sizeof(bufname));
	}
	if (nr_slots) {
		/* hack for fat_ioctl_filldir() */
		struct fat_ioctl_filldir_callback *p = dirent;

		p->longname = fill_name;
		p->long_len = fill_len;
		p->shortname = bufname;
		p->short_len = i;
		fill_name = NULL;
		fill_len = 0;
	} else {
		fill_name = bufname;
		fill_len = i;
	}

start_filldir:
	lpos = cpos - (nr_slots + 1) * sizeof(struct msdos_dir_entry);
	if (!memcmp(de->name, MSDOS_DOT, MSDOS_NAME))
		inum = inode->i_ino;
	else if (!memcmp(de->name, MSDOS_DOTDOT, MSDOS_NAME)) {
		inum = parent_ino(filp->f_path.dentry);
	} else {
		loff_t i_pos = fat_make_i_pos(sb, bh, de);
		struct inode *tmp = fat_iget(sb, i_pos);
		if (tmp) {
			inum = tmp->i_ino;
			iput(tmp);
		} else
			inum = iunique(sb, MSDOS_ROOT_INO);
	}

	if (filldir(dirent, fill_name, fill_len, *furrfu, inum,
		    (de->attr & ATTR_DIR) ? DT_DIR : DT_REG) < 0)
		goto fill_failed;

record_end:
	furrfu = &lpos;
	filp->f_pos = cpos;
	goto get_new;
end_of_dir:
	filp->f_pos = cpos;
fill_failed:
	brelse(bh);
	if (unicode)
		__putname(unicode);
out:
	unlock_super(sb);
	return ret;
}