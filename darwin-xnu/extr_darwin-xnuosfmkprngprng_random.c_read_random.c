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
 int CCKPRNG_NEED_ENTROPY ; 
 int CCKPRNG_OK ; 
 int /*<<< orphan*/  PRNG_CCKPRNG (int) ; 
 int /*<<< orphan*/  Reseed () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 TYPE_2__ prng ; 
 int prng_generate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

void
read_random(void * buffer, u_int numbytes)
{
	int err;

	lck_mtx_lock(prng.lock.mutex);

	/*
	 * Call PRNG, reseeding and retrying if requested.
	 */
	for (;;) {
		PRNG_CCKPRNG(err = prng_generate(&prng.ctx, numbytes, buffer));
		if (err == CCKPRNG_OK)
			break;
		if (err == CCKPRNG_NEED_ENTROPY) {
			Reseed();
			continue;
		}
		panic("read_random() error %d\n", err);
	}

	lck_mtx_unlock(prng.lock.mutex);
}