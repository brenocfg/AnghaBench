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
struct buffer_head {scalar_t__ b_size; scalar_t__ b_data; } ;
struct TYPE_2__ {scalar_t__ h_magic; scalar_t__ h_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFIRST (struct buffer_head*) ; 
 TYPE_1__* BHDR (struct buffer_head*) ; 
 int EIO ; 
 int EXT4_XATTR_MAGIC ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int ext4_xattr_check_names (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int
ext4_xattr_check_block(struct buffer_head *bh)
{
	int error;

	if (BHDR(bh)->h_magic != cpu_to_le32(EXT4_XATTR_MAGIC) ||
	    BHDR(bh)->h_blocks != cpu_to_le32(1))
		return -EIO;
	error = ext4_xattr_check_names(BFIRST(bh), bh->b_data + bh->b_size);
	return error;
}