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
 int /*<<< orphan*/  SYS_fanotify_init ; 
 int syscall (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int fanotify_init(unsigned flags, unsigned event_f_flags)
{
	return syscall(SYS_fanotify_init, flags, event_f_flags);
}