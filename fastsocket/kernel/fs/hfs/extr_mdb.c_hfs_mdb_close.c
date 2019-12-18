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
struct super_block {int s_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  mdb_bh; TYPE_1__* mdb; } ;
struct TYPE_3__ {int /*<<< orphan*/  drAtrb; } ;

/* Variables and functions */
 TYPE_2__* HFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  HFS_SB_ATTRIB_INCNSTNT ; 
 int /*<<< orphan*/  HFS_SB_ATTRIB_UNMNT ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 

void hfs_mdb_close(struct super_block *sb)
{
	/* update volume attributes */
	if (sb->s_flags & MS_RDONLY)
		return;
	HFS_SB(sb)->mdb->drAtrb |= cpu_to_be16(HFS_SB_ATTRIB_UNMNT);
	HFS_SB(sb)->mdb->drAtrb &= cpu_to_be16(~HFS_SB_ATTRIB_INCNSTNT);
	mark_buffer_dirty(HFS_SB(sb)->mdb_bh);
}