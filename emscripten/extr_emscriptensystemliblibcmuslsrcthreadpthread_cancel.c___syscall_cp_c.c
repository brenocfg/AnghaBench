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
typedef  int /*<<< orphan*/  syscall_arg_t ;
typedef  TYPE_1__* pthread_t ;
struct TYPE_3__ {int canceldisable; scalar_t__ cancel; } ;

/* Variables and functions */
 long EINTR ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int /*<<< orphan*/  SYS_close ; 
 long __cancel () ; 
 TYPE_1__* __pthread_self () ; 
 long __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long __syscall_cp_asm (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

long __syscall_cp_c(syscall_arg_t nr,
                    syscall_arg_t u, syscall_arg_t v, syscall_arg_t w,
                    syscall_arg_t x, syscall_arg_t y, syscall_arg_t z)
{
	pthread_t self;
	long r;
	int st;

	if ((st=(self=__pthread_self())->canceldisable)
	    && (st==PTHREAD_CANCEL_DISABLE || nr==SYS_close))
		return __syscall(nr, u, v, w, x, y, z);

	r = __syscall_cp_asm(&self->cancel, nr, u, v, w, x, y, z);
	if (r==-EINTR && nr!=SYS_close && self->cancel &&
	    self->canceldisable != PTHREAD_CANCEL_DISABLE)
		r = __cancel();
	return r;
}