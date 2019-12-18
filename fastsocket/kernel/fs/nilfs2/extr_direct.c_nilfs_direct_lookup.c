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
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NILFS_BMAP_INVALID_PTR ; 
 int /*<<< orphan*/  NILFS_DIRECT_KEY_MAX ; 
 int /*<<< orphan*/  nilfs_direct_get_ptr (struct nilfs_direct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_direct_lookup(const struct nilfs_bmap *bmap,
			       __u64 key, int level, __u64 *ptrp)
{
	struct nilfs_direct *direct;
	__u64 ptr;

	direct = (struct nilfs_direct *)bmap;
	if ((key > NILFS_DIRECT_KEY_MAX) ||
	    (level != 1) ||	/* XXX: use macro for level 1 */
	    ((ptr = nilfs_direct_get_ptr(direct, key)) ==
	     NILFS_BMAP_INVALID_PTR))
		return -ENOENT;

	if (ptrp != NULL)
		*ptrp = ptr;
	return 0;
}