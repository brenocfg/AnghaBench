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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct nouveau_timer {scalar_t__ (* read ) (struct nouveau_timer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NV_SUBDEV_CLASS ; 
 struct nouveau_timer* nouveau_timer (void*) ; 
 scalar_t__ nv_iclass (void*,int /*<<< orphan*/ ) ; 
 int nv_rd32 (void*,int) ; 
 int nv_ro32 (void*,int) ; 
 scalar_t__ stub1 (struct nouveau_timer*) ; 
 scalar_t__ stub2 (struct nouveau_timer*) ; 

bool
nouveau_timer_wait_ne(void *obj, u64 nsec, u32 addr, u32 mask, u32 data)
{
	struct nouveau_timer *ptimer = nouveau_timer(obj);
	u64 time0;

	time0 = ptimer->read(ptimer);
	do {
		if (nv_iclass(obj, NV_SUBDEV_CLASS)) {
			if ((nv_rd32(obj, addr) & mask) != data)
				return true;
		} else {
			if ((nv_ro32(obj, addr) & mask) != data)
				return true;
		}
	} while (ptimer->read(ptimer) - time0 < nsec);

	return false;
}