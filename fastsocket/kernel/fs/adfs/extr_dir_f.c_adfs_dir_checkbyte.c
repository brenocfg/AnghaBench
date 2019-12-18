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
typedef  int u8 ;
typedef  int u32 ;
struct buffer_head {int dummy; } ;
struct adfs_dir {TYPE_1__* sb; struct buffer_head** bh; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int s_blocksize_bits; } ;

/* Variables and functions */
 void* bufoff (struct buffer_head* const*,int) ; 
 int /*<<< orphan*/  dir_u32 (int) ; 
 scalar_t__ dir_u8 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int ror13 (int) ; 

__attribute__((used)) static u8
adfs_dir_checkbyte(const struct adfs_dir *dir)
{
	struct buffer_head * const *bh = dir->bh;
	const int blocksize_bits = dir->sb->s_blocksize_bits;
	union { __le32 *ptr32; u8 *ptr8; } ptr, end;
	u32 dircheck = 0;
	int last = 5 - 26;
	int i = 0;

	/*
	 * Accumulate each word up to the last whole
	 * word of the last directory entry.  This
	 * can spread across several buffer heads.
	 */
	do {
		last += 26;
		do {
			dircheck = le32_to_cpu(dir_u32(i)) ^ ror13(dircheck);

			i += sizeof(u32);
		} while (i < (last & ~3));
	} while (dir_u8(last) != 0);

	/*
	 * Accumulate the last few bytes.  These
	 * bytes will be within the same bh.
	 */
	if (i != last) {
		ptr.ptr8 = bufoff(bh, i);
		end.ptr8 = ptr.ptr8 + last - i;

		do {
			dircheck = *ptr.ptr8++ ^ ror13(dircheck);
		} while (ptr.ptr8 < end.ptr8);
	}

	/*
	 * The directory tail is in the final bh
	 * Note that contary to the RISC OS PRMs,
	 * the first few bytes are NOT included
	 * in the check.  All bytes are in the
	 * same bh.
	 */
	ptr.ptr8 = bufoff(bh, 2008);
	end.ptr8 = ptr.ptr8 + 36;

	do {
		__le32 v = *ptr.ptr32++;
		dircheck = le32_to_cpu(v) ^ ror13(dircheck);
	} while (ptr.ptr32 < end.ptr32);

	return (dircheck ^ (dircheck >> 8) ^ (dircheck >> 16) ^ (dircheck >> 24)) & 0xff;
}