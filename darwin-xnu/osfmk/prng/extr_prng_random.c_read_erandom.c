#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct ccdrbg_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  seed; int /*<<< orphan*/  drbg_info; struct ccdrbg_state** drbg_states; } ;

/* Variables and functions */
 int CCDRBG_STATUS_NEED_RESEED ; 
 int CCDRBG_STATUS_OK ; 
 size_t EARLY_RANDOM_SEED_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cc_clear (int,int /*<<< orphan*/ ) ; 
 int ccdrbg_generate (int /*<<< orphan*/ *,struct ccdrbg_state*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ccdrbg_reseed (int /*<<< orphan*/ *,struct ccdrbg_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cpu_number () ; 
 size_t entropy_readall (int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__ erandom ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static void
read_erandom(void * buffer, u_int numBytes)
{
	int cpu;
	int rc;
	size_t nbytes;
	struct ccdrbg_state * state;

	mp_disable_preemption();
	cpu   = cpu_number();
	state = erandom.drbg_states[cpu];
	assert(state);
	for (;;) {
		/* Generate output */
		rc = ccdrbg_generate(&erandom.drbg_info, state, numBytes, buffer, 0, NULL);
		if (rc == CCDRBG_STATUS_OK)
			break;
		if (rc == CCDRBG_STATUS_NEED_RESEED) {
			/* It's time to reseed. Get more entropy */
			nbytes = entropy_readall(erandom.seed, EARLY_RANDOM_SEED_SIZE);
			assert(nbytes >= EARLY_RANDOM_SEED_SIZE);
			rc = ccdrbg_reseed(&erandom.drbg_info, state, sizeof(erandom.seed), erandom.seed, 0, NULL);
			cc_clear(sizeof(erandom.seed), erandom.seed);
			if (rc == CCDRBG_STATUS_OK)
				continue;
			panic("read_erandom reseed error %d\n", rc);
		}
		panic("read_erandom ccdrbg error %d\n", rc);
	}
	mp_enable_preemption();
}