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
struct file_ra_state {int dummy; } ;
struct file {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  page_cache_sync_readahead (struct address_space*,struct file_ra_state*,struct file*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline void btrfs_force_ra(struct address_space *mapping,
				  struct file_ra_state *ra, struct file *file,
				  pgoff_t offset, unsigned long req_size)
{
	page_cache_sync_readahead(mapping, ra, file, offset, req_size);
}