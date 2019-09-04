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
struct TYPE_3__ {int canceldisable; scalar_t__ cancelasync; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CANCELED ; 
 TYPE_1__* __pthread_self () ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ ) ; 

void __cancel()
{
	pthread_t self = __pthread_self();
	self->canceldisable = 1;
	self->cancelasync = 0;
	pthread_exit(PTHREAD_CANCELED);
}