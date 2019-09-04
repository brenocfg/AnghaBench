#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_t ;
struct TYPE_4__ {scalar_t__ unblock_cancel; scalar_t__ cancelasync; scalar_t__ canceldisable; scalar_t__ cancelbuf; scalar_t__ cancel; } ;

/* Variables and functions */
 TYPE_1__* __pthread_self () ; 
 int /*<<< orphan*/  __pthread_tsd_run_dtors (TYPE_1__*) ; 
 int /*<<< orphan*/  __reset_tls () ; 
 int /*<<< orphan*/  longjmp (void*,int) ; 

__attribute__((used)) static void cleanup_fromsig(void *p)
{
	pthread_t self = __pthread_self();
	__pthread_tsd_run_dtors(self);
	self->cancel = 0;
	self->cancelbuf = 0;
	self->canceldisable = 0;
	self->cancelasync = 0;
	self->unblock_cancel = 0;
	__reset_tls();
	longjmp(p, 1);
}