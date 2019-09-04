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
struct TYPE_3__ {scalar_t__ canceldisable; scalar_t__ cancelasync; } ;

/* Variables and functions */
 long ECANCELED ; 
 int /*<<< orphan*/  PTHREAD_CANCELED ; 
 scalar_t__ PTHREAD_CANCEL_DISABLE ; 
 scalar_t__ PTHREAD_CANCEL_ENABLE ; 
 TYPE_1__* __pthread_self () ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ ) ; 

long __cancel()
{
	pthread_t self = __pthread_self();
	if (self->canceldisable == PTHREAD_CANCEL_ENABLE || self->cancelasync)
		pthread_exit(PTHREAD_CANCELED);
	self->canceldisable = PTHREAD_CANCEL_DISABLE;
	return -ECANCELED;
}