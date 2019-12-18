#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  sival_int; } ;
struct TYPE_7__ {TYPE_2__ size_equivalent; } ;
struct user_sigevent {void* sigev_notify_attributes; void* sigev_notify_function; TYPE_3__ sigev_value; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_notify; } ;
struct TYPE_5__ {int /*<<< orphan*/  sival_int; } ;
struct TYPE_8__ {int /*<<< orphan*/  sival_int; TYPE_1__ size_equivalent; } ;
struct user64_sigevent {void* sigev_notify_attributes; void* sigev_notify_function; TYPE_4__ sigev_value; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_notify; } ;
struct user32_sigevent {void* sigev_notify_attributes; void* sigev_notify_function; TYPE_4__ sigev_value; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_notify; } ;
typedef  int /*<<< orphan*/  sigevent64 ;
typedef  int /*<<< orphan*/  sigevent32 ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 void* CAST_USER_ADDR_T (void*) ; 
 int EAGAIN ; 
 scalar_t__ USER_ADDR_NULL ; 
 int copyin (scalar_t__,struct user64_sigevent*,int) ; 
 scalar_t__ proc_is64bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aio_copy_in_sigev(proc_t procp, user_addr_t sigp, struct user_sigevent *sigev)
{
	int	result = 0;

	if (sigp == USER_ADDR_NULL)
		goto out;

	/*
	 * We need to munge aio_sigevent since it contains pointers.
	 * Since we do not know if sigev_value is an int or a ptr we do
	 * NOT cast the ptr to a user_addr_t.   This means if we send
	 * this info back to user space we need to remember sigev_value
	 * was not expanded for the 32-bit case.
	 *
	 * Notes:	 This does NOT affect us since we don't support
	 *		sigev_value yet in the aio context.
	 */
	if ( proc_is64bit(procp) ) {
		struct user64_sigevent sigevent64;

		result = copyin( sigp, &sigevent64, sizeof(sigevent64) );
		if ( result == 0 ) {
			sigev->sigev_notify = sigevent64.sigev_notify;
			sigev->sigev_signo = sigevent64.sigev_signo;
			sigev->sigev_value.size_equivalent.sival_int = sigevent64.sigev_value.size_equivalent.sival_int;
			sigev->sigev_notify_function = sigevent64.sigev_notify_function;
			sigev->sigev_notify_attributes = sigevent64.sigev_notify_attributes;
		}
		
	} else {
		struct user32_sigevent sigevent32;

		result = copyin( sigp, &sigevent32, sizeof(sigevent32) );
		if ( result == 0 ) {
			sigev->sigev_notify = sigevent32.sigev_notify;
			sigev->sigev_signo = sigevent32.sigev_signo;
			sigev->sigev_value.size_equivalent.sival_int = sigevent32.sigev_value.sival_int;
			sigev->sigev_notify_function = CAST_USER_ADDR_T(sigevent32.sigev_notify_function);
			sigev->sigev_notify_attributes = CAST_USER_ADDR_T(sigevent32.sigev_notify_attributes);
		}
	}

	if ( result != 0 ) {
		result = EAGAIN;
	}

out:
	return (result);
}