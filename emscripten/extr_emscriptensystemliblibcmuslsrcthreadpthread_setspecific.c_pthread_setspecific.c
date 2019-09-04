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
struct pthread {void const** tsd; int tsd_used; } ;
typedef  size_t pthread_key_t ;

/* Variables and functions */
 struct pthread* __pthread_self () ; 

int pthread_setspecific(pthread_key_t k, const void *x)
{
	struct pthread *self = __pthread_self();
	/* Avoid unnecessary COW */
	if (self->tsd[k] != x) {
		self->tsd[k] = (void *)x;
		self->tsd_used = 1;
	}
	return 0;
}