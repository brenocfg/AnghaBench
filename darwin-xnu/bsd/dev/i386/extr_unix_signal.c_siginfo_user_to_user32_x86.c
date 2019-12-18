#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sival_ptr; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pad; int /*<<< orphan*/  si_band; TYPE_2__ si_value; int /*<<< orphan*/  si_addr; int /*<<< orphan*/  si_status; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_code; int /*<<< orphan*/  si_errno; int /*<<< orphan*/  si_signo; } ;
typedef  TYPE_3__ user_siginfo_t ;
struct TYPE_7__ {void* sival_ptr; } ;
struct TYPE_10__ {int /*<<< orphan*/ * __pad; int /*<<< orphan*/  si_band; TYPE_1__ si_value; void* si_addr; int /*<<< orphan*/  si_status; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_code; int /*<<< orphan*/  si_errno; int /*<<< orphan*/  si_signo; } ;
typedef  TYPE_4__ user32_siginfo_t ;

/* Variables and functions */
 void* CAST_DOWN_EXPLICIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user32_addr_t ; 

__attribute__((used)) static void
siginfo_user_to_user32_x86(user_siginfo_t *in, user32_siginfo_t *out)
{
	out->si_signo	= in->si_signo;
	out->si_errno	= in->si_errno;
	out->si_code	= in->si_code;
	out->si_pid	= in->si_pid;
	out->si_uid	= in->si_uid;
	out->si_status	= in->si_status;
	out->si_addr	= CAST_DOWN_EXPLICIT(user32_addr_t,in->si_addr);
	/* following cast works for sival_int because of padding */
	out->si_value.sival_ptr	= CAST_DOWN_EXPLICIT(user32_addr_t,in->si_value.sival_ptr);
	out->si_band	= in->si_band;			/* range reduction */
	out->__pad[0]	= in->pad[0];			/* mcontext.ss.r1 */
}