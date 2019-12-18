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
struct inode {TYPE_1__* i_sb; } ;
struct dx_entry {int dummy; } ;
struct TYPE_2__ {unsigned int s_blocksize; } ;

/* Variables and functions */
 unsigned int EXT4_DIR_REC_LEN (int) ; 

__attribute__((used)) static inline unsigned dx_root_limit(struct inode *dir, unsigned infosize)
{
	unsigned entry_space = dir->i_sb->s_blocksize - EXT4_DIR_REC_LEN(1) -
		EXT4_DIR_REC_LEN(2) - infosize;
	return entry_space / sizeof(struct dx_entry);
}