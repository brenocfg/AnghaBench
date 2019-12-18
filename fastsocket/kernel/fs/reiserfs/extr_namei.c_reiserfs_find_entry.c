#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct treepath {int /*<<< orphan*/  pos_in_item; } ;
struct reiserfs_dir_entry {int /*<<< orphan*/  de_ih; int /*<<< orphan*/  de_entry_num; } ;
struct inode {TYPE_1__* i_sb; } ;
struct cpu_key {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int GOTO_PREVIOUS_ITEM ; 
 int IO_ERROR ; 
 int NAME_NOT_FOUND ; 
 int REISERFS_MAX_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_DIRENTRY ; 
 int /*<<< orphan*/  get_third_component (TYPE_1__*,char const*,int) ; 
 scalar_t__ le_ih_k_offset (int /*<<< orphan*/ ) ; 
 int linear_search_in_dir_item (struct cpu_key*,struct reiserfs_dir_entry*,char const*,int) ; 
 int /*<<< orphan*/  make_cpu_key (struct cpu_key*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pathrelse (struct treepath*) ; 
 int /*<<< orphan*/  reiserfs_error (TYPE_1__*,char*,char*) ; 
 int search_by_entry_key (TYPE_1__*,struct cpu_key*,struct treepath*,struct reiserfs_dir_entry*) ; 
 int /*<<< orphan*/  set_cpu_key_k_offset (struct cpu_key*,scalar_t__) ; 

__attribute__((used)) static int reiserfs_find_entry(struct inode *dir, const char *name, int namelen,
			       struct treepath *path_to_entry,
			       struct reiserfs_dir_entry *de)
{
	struct cpu_key key_to_search;
	int retval;

	if (namelen > REISERFS_MAX_NAME(dir->i_sb->s_blocksize))
		return NAME_NOT_FOUND;

	/* we will search for this key in the tree */
	make_cpu_key(&key_to_search, dir,
		     get_third_component(dir->i_sb, name, namelen),
		     TYPE_DIRENTRY, 3);

	while (1) {
		retval =
		    search_by_entry_key(dir->i_sb, &key_to_search,
					path_to_entry, de);
		if (retval == IO_ERROR) {
			reiserfs_error(dir->i_sb, "zam-7001", "io error");
			return IO_ERROR;
		}

		/* compare names for all entries having given hash value */
		retval =
		    linear_search_in_dir_item(&key_to_search, de, name,
					      namelen);
		if (retval != GOTO_PREVIOUS_ITEM) {
			/* there is no need to scan directory anymore. Given entry found or does not exist */
			path_to_entry->pos_in_item = de->de_entry_num;
			return retval;
		}

		/* there is left neighboring item of this directory and given entry can be there */
		set_cpu_key_k_offset(&key_to_search,
				     le_ih_k_offset(de->de_ih) - 1);
		pathrelse(path_to_entry);

	}			/* while (1) */
}