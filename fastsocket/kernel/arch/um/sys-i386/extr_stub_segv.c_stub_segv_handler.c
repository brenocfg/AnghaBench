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
struct sigcontext {int dummy; } ;
struct faultinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FAULTINFO_FROM_SC (struct faultinfo,struct sigcontext*) ; 
 scalar_t__ STUB_DATA ; 
 int /*<<< orphan*/  trap_myself () ; 

void __attribute__ ((__section__ (".__syscall_stub")))
stub_segv_handler(int sig)
{
	struct sigcontext *sc = (struct sigcontext *) (&sig + 1);

	GET_FAULTINFO_FROM_SC(*((struct faultinfo *) STUB_DATA), sc);

	trap_myself();
}