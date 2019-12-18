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
typedef  int uint64_t ;

/* Variables and functions */
 int OCFS2_BACKUP_SB_START ; 
 int OCFS2_MAX_BACKUP_SUPERBLOCKS ; 

__attribute__((used)) static inline uint64_t ocfs2_backup_super_blkno(int blocksize, int index)
{
	uint64_t offset = OCFS2_BACKUP_SB_START;

	if (index >= 0 && index < OCFS2_MAX_BACKUP_SUPERBLOCKS) {
		offset <<= (2 * index);
		offset /= blocksize;
		return offset;
	}

	return 0;
}