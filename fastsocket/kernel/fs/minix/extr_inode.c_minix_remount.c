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
struct super_block {int s_flags; } ;
struct minix_super_block {int s_state; } ;
struct minix_sb_info {int s_mount_state; scalar_t__ s_version; int /*<<< orphan*/  s_sbh; struct minix_super_block* s_ms; } ;

/* Variables and functions */
 int MINIX_ERROR_FS ; 
 scalar_t__ MINIX_V3 ; 
 int MINIX_VALID_FS ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 struct minix_sb_info* minix_sb (struct super_block*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int minix_remount (struct super_block * sb, int * flags, char * data)
{
	struct minix_sb_info * sbi = minix_sb(sb);
	struct minix_super_block * ms;

	ms = sbi->s_ms;
	if ((*flags & MS_RDONLY) == (sb->s_flags & MS_RDONLY))
		return 0;
	if (*flags & MS_RDONLY) {
		if (ms->s_state & MINIX_VALID_FS ||
		    !(sbi->s_mount_state & MINIX_VALID_FS))
			return 0;
		/* Mounting a rw partition read-only. */
		if (sbi->s_version != MINIX_V3)
			ms->s_state = sbi->s_mount_state;
		mark_buffer_dirty(sbi->s_sbh);
	} else {
	  	/* Mount a partition which is read-only, read-write. */
		if (sbi->s_version != MINIX_V3) {
			sbi->s_mount_state = ms->s_state;
			ms->s_state &= ~MINIX_VALID_FS;
		} else {
			sbi->s_mount_state = MINIX_VALID_FS;
		}
		mark_buffer_dirty(sbi->s_sbh);

		if (!(sbi->s_mount_state & MINIX_VALID_FS))
			printk("MINIX-fs warning: remounting unchecked fs, "
				"running fsck is recommended\n");
		else if ((sbi->s_mount_state & MINIX_ERROR_FS))
			printk("MINIX-fs warning: remounting fs with errors, "
				"running fsck is recommended\n");
	}
	return 0;
}