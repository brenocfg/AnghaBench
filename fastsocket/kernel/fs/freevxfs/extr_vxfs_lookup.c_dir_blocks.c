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
typedef  int u_long ;
struct inode {int i_size; TYPE_1__* i_sb; } ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */

__attribute__((used)) static inline u_long
dir_blocks(struct inode *ip)
{
	u_long			bsize = ip->i_sb->s_blocksize;
	return (ip->i_size + bsize - 1) & ~(bsize - 1);
}