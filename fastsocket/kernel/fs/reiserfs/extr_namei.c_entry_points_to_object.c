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
struct reiserfs_dir_entry {scalar_t__ de_objectid; scalar_t__ de_entry_num; scalar_t__ de_deh; } ;
struct inode {scalar_t__ i_ino; int /*<<< orphan*/ * i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  de_still_valid (char const*,int,struct reiserfs_dir_entry*) ; 
 scalar_t__ de_visible (scalar_t__) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int entry_points_to_object(const char *name, int len,
				  struct reiserfs_dir_entry *de,
				  struct inode *inode)
{
	if (!de_still_valid(name, len, de))
		return 0;

	if (inode) {
		if (!de_visible(de->de_deh + de->de_entry_num))
			reiserfs_panic(inode->i_sb, "vs-7042",
				       "entry must be visible");
		return (de->de_objectid == inode->i_ino) ? 1 : 0;
	}

	/* this must be added hidden entry */
	if (de_visible(de->de_deh + de->de_entry_num))
		reiserfs_panic(NULL, "vs-7043", "entry must be visible");

	return 1;
}