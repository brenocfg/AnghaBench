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

/* Variables and functions */
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quit (int) ; 
 int /*<<< orphan*/  sigactive ; 
 int sigflags ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 

void
handle_int(int signo)
{
	if (!sigactive)
		quit(1);
	sigflags &= ~(1 << (signo - 1));
#ifdef _POSIX_SOURCE
	siglongjmp(env, -1);
#else
	longjmp(env, -1);
#endif
}