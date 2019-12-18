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
typedef  int /*<<< orphan*/  u32 ;
struct nilfs_super_root {int /*<<< orphan*/  sr_sum; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 scalar_t__ NILFS_SR_BYTES ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 

__attribute__((used)) static void nilfs_fill_in_super_root_crc(struct buffer_head *bh_sr, u32 seed)
{
	struct nilfs_super_root *raw_sr =
		(struct nilfs_super_root *)bh_sr->b_data;
	u32 crc;

	crc = crc32_le(seed,
		       (unsigned char *)raw_sr + sizeof(raw_sr->sr_sum),
		       NILFS_SR_BYTES - sizeof(raw_sr->sr_sum));
	raw_sr->sr_sum = cpu_to_le32(crc);
}