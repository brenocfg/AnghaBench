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
struct _throttle_io_info_t {scalar_t__ throttle_refcnt; int /*<<< orphan*/  throttle_lock; scalar_t__ throttle_alloc; } ;
typedef  int SInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ALLOC_THROTTLE_INFO (char*,struct _throttle_io_info_t*,...) ; 
 int /*<<< orphan*/  FREE (struct _throttle_io_info_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int OSDecrementAtomic (scalar_t__*) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  throttle_lock_grp ; 

__attribute__((used)) static int
throttle_info_rel(struct _throttle_io_info_t *info)
{
	SInt32 oldValue = OSDecrementAtomic(&info->throttle_refcnt);

	DEBUG_ALLOC_THROTTLE_INFO("refcnt = %d info = %p\n", 
		info, (int)(oldValue -1), info );

	/* The reference count just went negative, very bad */
	if (oldValue == 0)
		panic("throttle info ref cnt went negative!");

	/* 
	 * Once reference count is zero, no one else should be able to take a 
	 * reference 
	 */
	if ((info->throttle_refcnt == 0) && (info->throttle_alloc)) {
		DEBUG_ALLOC_THROTTLE_INFO("Freeing info = %p\n", info);
		
		lck_mtx_destroy(&info->throttle_lock, throttle_lock_grp);
		FREE(info, M_TEMP); 
	}
	return oldValue;
}