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
typedef  int wchar_t ;
struct super_block {int dummy; } ;
struct nls_table {int dummy; } ;
struct TYPE_2__ {unsigned short shortname; } ;
struct msdos_sb_info {TYPE_1__ options; struct nls_table* nls_disk; } ;
struct msdos_dir_entry {scalar_t__* name; int attr; int lcase; } ;
struct inode {struct super_block* i_sb; } ;
struct fat_slot_info {unsigned char nr_slots; struct msdos_dir_entry* de; struct buffer_head* bh; int /*<<< orphan*/  i_pos; scalar_t__ slot_off; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  bufname ;

/* Variables and functions */
 int ATTR_EXT ; 
 int ATTR_VOLUME ; 
 int CASE_LOWER_BASE ; 
 int CASE_LOWER_EXT ; 
 scalar_t__ DELETED_FLAG ; 
 int ENOENT ; 
 int FAT_MAX_SHORT_SIZE ; 
 int FAT_MAX_UNI_CHARS ; 
 int FAT_MAX_UNI_SIZE ; 
 scalar_t__ IS_FREE (scalar_t__*) ; 
 int MSDOS_NAME ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int PARSE_EOF ; 
 int PARSE_INVALID ; 
 int PARSE_NOT_LONGNAME ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  __putname (int*) ; 
 int fat_get_entry (struct inode*,scalar_t__*,struct buffer_head**,struct msdos_dir_entry**) ; 
 int /*<<< orphan*/  fat_make_i_pos (struct super_block*,struct buffer_head*,struct msdos_dir_entry*) ; 
 scalar_t__ fat_name_match (struct msdos_sb_info*,unsigned char const*,int,void*,int) ; 
 int fat_parse_long (struct inode*,scalar_t__*,struct buffer_head**,struct msdos_dir_entry**,int**,unsigned char*) ; 
 int /*<<< orphan*/  fat_short2uni (struct nls_table*,char*,int,int*) ; 
 int fat_shortname2uni (struct nls_table*,unsigned char*,int,int*,unsigned short,int) ; 
 int fat_uni_to_x8 (struct msdos_sb_info*,int*,void*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__*,int) ; 

int fat_search_long(struct inode *inode, const unsigned char *name,
		    int name_len, struct fat_slot_info *sinfo)
{
	struct super_block *sb = inode->i_sb;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	struct buffer_head *bh = NULL;
	struct msdos_dir_entry *de;
	struct nls_table *nls_disk = sbi->nls_disk;
	unsigned char nr_slots;
	wchar_t bufuname[14];
	wchar_t *unicode = NULL;
	unsigned char work[MSDOS_NAME];
	unsigned char bufname[FAT_MAX_SHORT_SIZE];
	unsigned short opt_shortname = sbi->options.shortname;
	loff_t cpos = 0;
	int chl, i, j, last_u, err, len;

	err = -ENOENT;
	while (1) {
		if (fat_get_entry(inode, &cpos, &bh, &de) == -1)
			goto end_of_dir;
parse_record:
		nr_slots = 0;
		if (de->name[0] == DELETED_FLAG)
			continue;
		if (de->attr != ATTR_EXT && (de->attr & ATTR_VOLUME))
			continue;
		if (de->attr != ATTR_EXT && IS_FREE(de->name))
			continue;
		if (de->attr == ATTR_EXT) {
			int status = fat_parse_long(inode, &cpos, &bh, &de,
						    &unicode, &nr_slots);
			if (status < 0) {
				err = status;
				goto end_of_dir;
			} else if (status == PARSE_INVALID)
				continue;
			else if (status == PARSE_NOT_LONGNAME)
				goto parse_record;
			else if (status == PARSE_EOF)
				goto end_of_dir;
		}

		memcpy(work, de->name, sizeof(de->name));
		/* see namei.c, msdos_format_name */
		if (work[0] == 0x05)
			work[0] = 0xE5;
		for (i = 0, j = 0, last_u = 0; i < 8;) {
			if (!work[i])
				break;
			chl = fat_shortname2uni(nls_disk, &work[i], 8 - i,
						&bufuname[j++], opt_shortname,
						de->lcase & CASE_LOWER_BASE);
			if (chl <= 1) {
				if (work[i] != ' ')
					last_u = j;
			} else {
				last_u = j;
			}
			i += chl;
		}
		j = last_u;
		fat_short2uni(nls_disk, ".", 1, &bufuname[j++]);
		for (i = 8; i < MSDOS_NAME;) {
			if (!work[i])
				break;
			chl = fat_shortname2uni(nls_disk, &work[i],
						MSDOS_NAME - i,
						&bufuname[j++], opt_shortname,
						de->lcase & CASE_LOWER_EXT);
			if (chl <= 1) {
				if (work[i] != ' ')
					last_u = j;
			} else {
				last_u = j;
			}
			i += chl;
		}
		if (!last_u)
			continue;

		/* Compare shortname */
		bufuname[last_u] = 0x0000;
		len = fat_uni_to_x8(sbi, bufuname, bufname, sizeof(bufname));
		if (fat_name_match(sbi, name, name_len, bufname, len))
			goto found;

		if (nr_slots) {
			void *longname = unicode + FAT_MAX_UNI_CHARS;
			int size = PATH_MAX - FAT_MAX_UNI_SIZE;

			/* Compare longname */
			len = fat_uni_to_x8(sbi, unicode, longname, size);
			if (fat_name_match(sbi, name, name_len, longname, len))
				goto found;
		}
	}

found:
	nr_slots++;	/* include the de */
	sinfo->slot_off = cpos - nr_slots * sizeof(*de);
	sinfo->nr_slots = nr_slots;
	sinfo->de = de;
	sinfo->bh = bh;
	sinfo->i_pos = fat_make_i_pos(sb, sinfo->bh, sinfo->de);
	err = 0;
end_of_dir:
	if (unicode)
		__putname(unicode);

	return err;
}