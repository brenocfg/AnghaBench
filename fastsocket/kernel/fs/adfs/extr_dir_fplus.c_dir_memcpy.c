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
struct super_block {unsigned int s_blocksize_bits; int s_blocksize; } ;
struct adfs_dir {TYPE_1__** bh; struct super_block* sb; } ;
struct TYPE_2__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void
dir_memcpy(struct adfs_dir *dir, unsigned int offset, void *to, int len)
{
	struct super_block *sb = dir->sb;
	unsigned int buffer, partial, remainder;

	buffer = offset >> sb->s_blocksize_bits;
	offset &= sb->s_blocksize - 1;

	partial = sb->s_blocksize - offset;

	if (partial >= len)
		memcpy(to, dir->bh[buffer]->b_data + offset, len);
	else {
		char *c = (char *)to;

		remainder = len - partial;

		memcpy(c, dir->bh[buffer]->b_data + offset, partial);
		memcpy(c + partial, dir->bh[buffer + 1]->b_data, remainder);
	}
}