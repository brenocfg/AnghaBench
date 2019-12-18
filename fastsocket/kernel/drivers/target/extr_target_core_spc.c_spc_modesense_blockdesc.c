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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int spc_modesense_blockdesc(unsigned char *buf, u64 blocks, u32 block_size)
{
	*buf++ = 8;
	put_unaligned_be32(min(blocks, 0xffffffffull), buf);
	buf += 4;
	put_unaligned_be32(block_size, buf);
	return 9;
}