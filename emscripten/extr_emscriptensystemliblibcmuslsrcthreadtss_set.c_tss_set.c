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
typedef  size_t tss_t ;
struct pthread {void** tsd; int tsd_used; } ;

/* Variables and functions */
 struct pthread* __pthread_self () ; 
 int thrd_success ; 

int tss_set(tss_t k, void *x)
{
	struct pthread *self = __pthread_self();
	/* Avoid unnecessary COW */
	if (self->tsd[k] != x) {
		self->tsd[k] = x;
		self->tsd_used = 1;
	}
	return thrd_success;
}