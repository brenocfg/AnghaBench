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
struct _throttle_io_info_t {scalar_t__ throttle_alloc; int /*<<< orphan*/  throttle_refcnt; } ;
typedef  int SInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ALLOC_THROTTLE_INFO (char*,struct _throttle_io_info_t*,int,struct _throttle_io_info_t*) ; 
 int OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static SInt32
throttle_info_ref(struct _throttle_io_info_t *info)
{
	SInt32 oldValue = OSIncrementAtomic(&info->throttle_refcnt);

	DEBUG_ALLOC_THROTTLE_INFO("refcnt = %d info = %p\n", 
		info, (int)(oldValue -1), info );
	/* Allocated items should never have a reference of zero */
	if (info->throttle_alloc && (oldValue == 0))
		panic("Taking a reference without calling create throttle info!\n");

	return oldValue;
}