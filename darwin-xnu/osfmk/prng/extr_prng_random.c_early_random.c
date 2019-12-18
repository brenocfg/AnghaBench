#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct ccdrbg_state {int dummy; } ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  ps ;
typedef  int /*<<< orphan*/  nonce ;
struct TYPE_8__ {scalar_t__ buffer; } ;
struct TYPE_7__ {int size; } ;
struct TYPE_6__ {int seedset; TYPE_2__ drbg_info; int /*<<< orphan*/  seed; struct ccdrbg_state** drbg_states; scalar_t__ master_drbg_state; int /*<<< orphan*/  drbg_custom; } ;

/* Variables and functions */
 int CCDRBG_STATUS_OK ; 
 int /*<<< orphan*/  EARLY_RANDOM_SEED_SIZE ; 
 TYPE_5__ EntropyData ; 
 int PE_get_random_seed (unsigned char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cc_clear (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdrbg_factory_nisthmac (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ccdrbg_generate (TYPE_2__*,struct ccdrbg_state*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ccdrbg_init (TYPE_2__*,struct ccdrbg_state*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  entropy_readall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ erandom ; 
 size_t master_cpu ; 
 int /*<<< orphan*/  ml_get_timebase () ; 
 int /*<<< orphan*/  panic (char*,int,...) ; 
 int /*<<< orphan*/  read_erandom (int /*<<< orphan*/ *,int) ; 

uint64_t
early_random(void)
{
	uint32_t cnt = 0;
	uint64_t result;
	uint64_t nonce;
	int rc;
	int ps;
	struct ccdrbg_state * state;

	if (!erandom.seedset) {
		erandom.seedset = 1;
		cnt             = PE_get_random_seed((unsigned char *)EntropyData.buffer, sizeof(EntropyData.buffer));

		if (cnt < sizeof(EntropyData.buffer)) {
			/*
			 * Insufficient entropy is fatal.  We must fill the
			 * entire entropy buffer during initializaton.
			 */
			panic("EntropyData needed %lu bytes, but got %u.\n", sizeof(EntropyData.buffer), cnt);
		}

		entropy_readall(&erandom.seed, EARLY_RANDOM_SEED_SIZE);

		/* Init DRBG for NIST HMAC */
		ccdrbg_factory_nisthmac(&erandom.drbg_info, &erandom.drbg_custom);
		assert(erandom.drbg_info.size <= sizeof(erandom.master_drbg_state));
		state                           = (struct ccdrbg_state *)erandom.master_drbg_state;
		erandom.drbg_states[master_cpu] = state;

		/*
		 * Init our DBRG from the boot entropy and a timestamp as nonce
		 * and the cpu number as personalization.
		 */
		assert(sizeof(erandom.seed) > sizeof(nonce));
		nonce = ml_get_timebase();
		ps    = 0; /* boot cpu */
		rc    = ccdrbg_init(&erandom.drbg_info, state, sizeof(erandom.seed), erandom.seed, sizeof(nonce), &nonce, sizeof(ps), &ps);
		cc_clear(sizeof(nonce), &nonce);
		if (rc != CCDRBG_STATUS_OK)
			panic("ccdrbg_init() returned %d", rc);

		/* Generate output */
		rc = ccdrbg_generate(&erandom.drbg_info, state, sizeof(result), &result, 0, NULL);
		if (rc != CCDRBG_STATUS_OK)
			panic("ccdrbg_generate() returned %d", rc);

		return result;
	};

	read_erandom(&result, sizeof(result));

	return result;
}