#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {TYPE_1__ lock; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 TYPE_2__ prng ; 
 int prng_reseed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

int
write_random(void * buffer, u_int numbytes)
{
#if PERMIT_WRITE_RANDOM
	int err;

	lck_mtx_lock(prng.lock.mutex);
	err = prng_reseed(&prng.ctx, numbytes, buffer);
	lck_mtx_unlock(prng.lock.mutex);

	return err ? EIO : 0;
#else
#pragma unused(buffer, numbytes)
	return 0;
#endif
}