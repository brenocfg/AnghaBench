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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */

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