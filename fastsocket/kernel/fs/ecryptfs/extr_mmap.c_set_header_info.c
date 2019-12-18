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
struct ecryptfs_crypt_stat {size_t num_header_bytes_at_front; } ;

/* Variables and functions */
 size_t ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE ; 
 int /*<<< orphan*/  ecryptfs_write_header_metadata (char*,struct ecryptfs_crypt_stat*,size_t*) ; 

__attribute__((used)) static void set_header_info(char *page_virt,
			    struct ecryptfs_crypt_stat *crypt_stat)
{
	size_t written;
	size_t save_num_header_bytes_at_front =
		crypt_stat->num_header_bytes_at_front;

	crypt_stat->num_header_bytes_at_front =
		ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE;
	ecryptfs_write_header_metadata(page_virt + 20, crypt_stat, &written);
	crypt_stat->num_header_bytes_at_front =
		save_num_header_bytes_at_front;
}