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
struct nilfs_bmap {int dummy; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ NILFS_BMAP_INVALID_PTR ; 
 scalar_t__ NILFS_DIRECT_KEY_MAX ; 
 scalar_t__ NILFS_DIRECT_KEY_MIN ; 
 scalar_t__ nilfs_direct_get_ptr (struct nilfs_direct*,scalar_t__) ; 

__attribute__((used)) static int nilfs_direct_last_key(const struct nilfs_bmap *bmap, __u64 *keyp)
{
	struct nilfs_direct *direct;
	__u64 key, lastkey;

	direct = (struct nilfs_direct *)bmap;
	lastkey = NILFS_DIRECT_KEY_MAX + 1;
	for (key = NILFS_DIRECT_KEY_MIN; key <= NILFS_DIRECT_KEY_MAX; key++)
		if (nilfs_direct_get_ptr(direct, key) !=
		    NILFS_BMAP_INVALID_PTR)
			lastkey = key;

	if (lastkey == NILFS_DIRECT_KEY_MAX + 1)
		return -ENOENT;

	*keyp = lastkey;

	return 0;
}