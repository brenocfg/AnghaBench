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
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  os_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  W_EXITCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int exit_with_reason (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jetsam_do_kill(proc_t p, int jetsam_flags, os_reason_t jetsam_reason) {
	int error = 0;
	error = exit_with_reason(p, W_EXITCODE(0, SIGKILL), (int *)NULL, FALSE, FALSE, jetsam_flags, jetsam_reason);
	return(error);
}