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
struct v9fs_cookie {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SLAB_MEM_SPREAD ; 
 int SLAB_RECLAIM_ACCOUNT ; 
 int /*<<< orphan*/  init_once ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcookie_cache ; 

__attribute__((used)) static int v9fs_init_vcookiecache(void)
{
	vcookie_cache = kmem_cache_create("vcookie_cache",
					  sizeof(struct v9fs_cookie),
					  0, (SLAB_RECLAIM_ACCOUNT|
					      SLAB_MEM_SPREAD),
					  init_once);
	if (!vcookie_cache)
		return -ENOMEM;

	return 0;
}