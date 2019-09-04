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
struct TYPE_3__ {int /*<<< orphan*/  canceldisable; scalar_t__ cancel; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cancel () ; 
 TYPE_1__* pthread_self () ; 

void __testcancel()
{
	pthread_t self = pthread_self();
	if (self->cancel && !self->canceldisable)
		__cancel();
}