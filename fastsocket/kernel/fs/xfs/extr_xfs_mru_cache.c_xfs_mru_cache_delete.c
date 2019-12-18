#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* free_func ) (unsigned long,void*) ;} ;
typedef  TYPE_1__ xfs_mru_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned long,void*) ; 
 void* xfs_mru_cache_remove (TYPE_1__*,unsigned long) ; 

void
xfs_mru_cache_delete(
	xfs_mru_cache_t	*mru,
	unsigned long	key)
{
	void		*value = xfs_mru_cache_remove(mru, key);

	if (value)
		mru->free_func(key, value);
}