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
 int /*<<< orphan*/  nilfs_bmap_ptr_to_dptr (int) ; 
 int /*<<< orphan*/ * nilfs_direct_dptrs (struct nilfs_direct*) ; 

__attribute__((used)) static inline void nilfs_direct_set_ptr(struct nilfs_direct *direct,
					__u64 key, __u64 ptr)
{
	*(nilfs_direct_dptrs(direct) + key) = nilfs_bmap_ptr_to_dptr(ptr);
}