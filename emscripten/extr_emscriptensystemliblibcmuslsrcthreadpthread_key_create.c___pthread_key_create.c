#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_t ;
typedef  unsigned int pthread_key_t ;
struct TYPE_3__ {scalar_t__ tsd; } ;

/* Variables and functions */
 int EAGAIN ; 
 uintptr_t PTHREAD_KEYS_MAX ; 
 TYPE_1__* __pthread_self () ; 
 scalar_t__ __pthread_tsd_main ; 
 int /*<<< orphan*/  a_cas_p (scalar_t__,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ keys ; 
 void nodtor (void*) ; 

int __pthread_key_create(pthread_key_t *k, void (*dtor)(void *))
{
	unsigned i = (uintptr_t)&k / 16 % PTHREAD_KEYS_MAX;
	unsigned j = i;
	pthread_t self = __pthread_self();

	/* This can only happen in the main thread before
	 * pthread_create has been called. */
	if (!self->tsd) self->tsd = __pthread_tsd_main;

	if (!dtor) dtor = nodtor;
	do {
		if (!a_cas_p(keys+j, 0, (void *)dtor)) {
			*k = j;
			return 0;
		}
	} while ((j=(j+1)%PTHREAD_KEYS_MAX) != i);
	return EAGAIN;
}