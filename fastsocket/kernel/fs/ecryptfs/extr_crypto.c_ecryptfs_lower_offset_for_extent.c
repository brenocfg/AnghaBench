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
struct ecryptfs_crypt_stat {int num_header_bytes_at_front; int extent_size; } ;
typedef  int loff_t ;

/* Variables and functions */

__attribute__((used)) static void ecryptfs_lower_offset_for_extent(loff_t *offset, loff_t extent_num,
					     struct ecryptfs_crypt_stat *crypt_stat)
{
	(*offset) = (crypt_stat->num_header_bytes_at_front
		     + (crypt_stat->extent_size * extent_num));
}