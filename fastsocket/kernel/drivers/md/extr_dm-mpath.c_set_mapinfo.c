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
union map_info {struct dm_mpath_io* ptr; } ;
struct multipath {int /*<<< orphan*/  mpio_pool; } ;
struct dm_mpath_io {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct dm_mpath_io* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dm_mpath_io*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_mapinfo(struct multipath *m, union map_info *info)
{
	struct dm_mpath_io *mpio;

	mpio = mempool_alloc(m->mpio_pool, GFP_ATOMIC);
	if (!mpio)
		return -ENOMEM;

	memset(mpio, 0, sizeof(*mpio));
	info->ptr = mpio;

	return 0;
}