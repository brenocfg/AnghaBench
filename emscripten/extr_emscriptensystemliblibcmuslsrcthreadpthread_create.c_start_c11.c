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
typedef  TYPE_1__* pthread_t ;
struct TYPE_2__ {void* start_arg; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pthread_exit (void*) ; 

__attribute__((used)) static int start_c11(void *p)
{
	pthread_t self = p;
	int (*start)(void*) = (int(*)(void*)) self->start;
	__pthread_exit((void *)(uintptr_t)start(self->start_arg));
	return 0;
}