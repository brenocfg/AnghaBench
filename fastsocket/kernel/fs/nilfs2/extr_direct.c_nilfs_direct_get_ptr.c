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
struct nilfs_direct {int dummy; } ;
typedef  int __u64 ;

/* Variables and functions */
 int nilfs_bmap_dptr_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nilfs_direct_dptrs (struct nilfs_direct const*) ; 

__attribute__((used)) static inline __u64
nilfs_direct_get_ptr(const struct nilfs_direct *direct, __u64 key)
{
	return nilfs_bmap_dptr_to_ptr(*(nilfs_direct_dptrs(direct) + key));
}