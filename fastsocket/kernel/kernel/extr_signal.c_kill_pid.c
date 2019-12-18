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
struct pid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __si_special (int) ; 
 int kill_pid_info (int,int /*<<< orphan*/ ,struct pid*) ; 

int kill_pid(struct pid *pid, int sig, int priv)
{
	return kill_pid_info(sig, __si_special(priv), pid);
}