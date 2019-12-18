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
struct TYPE_4__ {int rng_init_done; int /*<<< orphan*/  rng; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_hmac_drbg_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  rng_init (TYPE_1__*) ; 

void
br_ssl_engine_inject_entropy(br_ssl_engine_context *cc,
	const void *data, size_t len)
{
	/*
	 * Externally provided entropy is assumed to be "good enough"
	 * (we cannot really test its quality) so if the RNG structure
	 * could be initialised at all, then we marked the RNG as
	 * "properly seeded".
	 */
	if (!rng_init(cc)) {
		return;
	}
	br_hmac_drbg_update(&cc->rng, data, len);
	cc->rng_init_done = 2;
}