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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  u8 ;
struct timespec {int dummy; } ;
struct fat_mount_options {int /*<<< orphan*/  utf8; int /*<<< orphan*/  unicode_xlate; } ;
struct msdos_sb_info {int /*<<< orphan*/  nls_disk; int /*<<< orphan*/  nls_io; struct fat_mount_options options; } ;
struct msdos_dir_slot {int id; unsigned char alias_checksum; int /*<<< orphan*/  name11_12; int /*<<< orphan*/  name5_10; int /*<<< orphan*/  name0_4; scalar_t__ start; scalar_t__ reserved; int /*<<< orphan*/  attr; } ;
struct msdos_dir_entry {unsigned char lcase; scalar_t__ size; void* starthi; void* start; int /*<<< orphan*/  ctime_cs; void* adate; void* cdate; void* date; void* ctime; void* time; int /*<<< orphan*/  attr; int /*<<< orphan*/  name; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int loff_t ;
typedef  void* __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ARCH ; 
 int /*<<< orphan*/  ATTR_DIR ; 
 int /*<<< orphan*/  ATTR_EXT ; 
 int ENOMEM ; 
 int MSDOS_NAME ; 
 struct msdos_sb_info* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __getname () ; 
 int /*<<< orphan*/  __putname (int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int) ; 
 unsigned char fat_checksum (unsigned char*) ; 
 int /*<<< orphan*/  fat_time_unix2fat (struct msdos_sb_info*,struct timespec*,void**,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatwchar_to16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int vfat_create_shortname (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned char*,unsigned char*) ; 
 int vfat_is_used_badchars (int /*<<< orphan*/ *,int) ; 
 int xlate_to_uni (unsigned char const*,int,unsigned char*,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfat_build_slots(struct inode *dir, const unsigned char *name,
			    int len, int is_dir, int cluster,
			    struct timespec *ts,
			    struct msdos_dir_slot *slots, int *nr_slots)
{
	struct msdos_sb_info *sbi = MSDOS_SB(dir->i_sb);
	struct fat_mount_options *opts = &sbi->options;
	struct msdos_dir_slot *ps;
	struct msdos_dir_entry *de;
	unsigned char cksum, lcase;
	unsigned char msdos_name[MSDOS_NAME];
	wchar_t *uname;
	__le16 time, date;
	u8 time_cs;
	int err, ulen, usize, i;
	loff_t offset;

	*nr_slots = 0;

	uname = __getname();
	if (!uname)
		return -ENOMEM;

	err = xlate_to_uni(name, len, (unsigned char *)uname, &ulen, &usize,
			   opts->unicode_xlate, opts->utf8, sbi->nls_io);
	if (err)
		goto out_free;

	err = vfat_is_used_badchars(uname, ulen);
	if (err)
		goto out_free;

	err = vfat_create_shortname(dir, sbi->nls_disk, uname, ulen,
				    msdos_name, &lcase);
	if (err < 0)
		goto out_free;
	else if (err == 1) {
		de = (struct msdos_dir_entry *)slots;
		err = 0;
		goto shortname;
	}

	/* build the entry of long file name */
	cksum = fat_checksum(msdos_name);

	*nr_slots = usize / 13;
	for (ps = slots, i = *nr_slots; i > 0; i--, ps++) {
		ps->id = i;
		ps->attr = ATTR_EXT;
		ps->reserved = 0;
		ps->alias_checksum = cksum;
		ps->start = 0;
		offset = (i - 1) * 13;
		fatwchar_to16(ps->name0_4, uname + offset, 5);
		fatwchar_to16(ps->name5_10, uname + offset + 5, 6);
		fatwchar_to16(ps->name11_12, uname + offset + 11, 2);
	}
	slots[0].id |= 0x40;
	de = (struct msdos_dir_entry *)ps;

shortname:
	/* build the entry of 8.3 alias name */
	(*nr_slots)++;
	memcpy(de->name, msdos_name, MSDOS_NAME);
	de->attr = is_dir ? ATTR_DIR : ATTR_ARCH;
	de->lcase = lcase;
	fat_time_unix2fat(sbi, ts, &time, &date, &time_cs);
	de->time = de->ctime = time;
	de->date = de->cdate = de->adate = date;
	de->ctime_cs = time_cs;
	de->start = cpu_to_le16(cluster);
	de->starthi = cpu_to_le16(cluster >> 16);
	de->size = 0;
out_free:
	__putname(uname);
	return err;
}