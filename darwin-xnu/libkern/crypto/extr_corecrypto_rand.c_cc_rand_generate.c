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
struct ccrng_state {int dummy; } ;
struct TYPE_2__ {struct ccrng_state* (* ccrng_fn ) (int*) ;} ;

/* Variables and functions */
 int ccrng_generate (struct ccrng_state*,size_t,void*) ; 
 TYPE_1__* g_crypto_funcs ; 
 struct ccrng_state* stub1 (int*) ; 

int
cc_rand_generate(void *out, size_t outlen)
{
	struct ccrng_state *rng_state = NULL;
	int error = -1;

	if (g_crypto_funcs) {
		rng_state = g_crypto_funcs->ccrng_fn(&error);
		if (rng_state != NULL) {
			error = ccrng_generate(rng_state, outlen, out);
		}
	}

	return error;
}