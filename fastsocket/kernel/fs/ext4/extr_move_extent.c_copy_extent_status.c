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
struct ext4_extent {int /*<<< orphan*/  ee_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_is_uninitialized (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_mark_uninitialized (struct ext4_extent*) ; 

__attribute__((used)) static void
copy_extent_status(struct ext4_extent *src, struct ext4_extent *dest)
{
	if (ext4_ext_is_uninitialized(src))
		ext4_ext_mark_uninitialized(dest);
	else
		dest->ee_len = cpu_to_le16(ext4_ext_get_actual_len(dest));
}