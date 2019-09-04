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
struct pthread {int cancelasync; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pthread* __pthread_self () ; 
 int /*<<< orphan*/  pthread_testcancel () ; 

int pthread_setcanceltype(int new, int *old)
{
	struct pthread *self = __pthread_self();
	if (new > 1U) return EINVAL;
	if (old) *old = self->cancelasync;
	self->cancelasync = new;
	if (new) pthread_testcancel();
	return 0;
}