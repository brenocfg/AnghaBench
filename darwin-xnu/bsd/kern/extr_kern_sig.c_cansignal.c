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
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int cansignal_nomac (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mac_proc_check_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
cansignal(proc_t src, kauth_cred_t uc_src, proc_t dst, int signum)
{
#if CONFIG_MACF
	if (mac_proc_check_signal(src, dst, signum)) {
		return 0;
	}
#endif

	return cansignal_nomac(src, uc_src, dst, signum);
}