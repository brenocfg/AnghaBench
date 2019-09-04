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
typedef  int /*<<< orphan*/  cckprng_ctx_t ;
struct TYPE_2__ {int (* generate ) (int /*<<< orphan*/ ,size_t,void*) ;} ;

/* Variables and functions */
 int CCKPRNG_ABORT ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__* prng_fns ; 
 int stub1 (int /*<<< orphan*/ ,size_t,void*) ; 

__attribute__((used)) static int
prng_generate(cckprng_ctx_t ctx, size_t nbytes, void * out)
{
	int err = prng_fns->generate(ctx, nbytes, out);
	if (err == CCKPRNG_ABORT) {
		panic("prng_generate");
	}
	return err;
}