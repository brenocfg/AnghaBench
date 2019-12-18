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
typedef  long uint64_t ;
struct timespec {long tv_sec; long tv_nsec; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 long NSEC_PER_SEC ; 
 int PCATCH ; 
 int PRIBIO ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,struct timespec*) ; 
 int /*<<< orphan*/  sys_override_lock ; 
 int /*<<< orphan*/  sys_override_wait ; 

__attribute__((used)) static __attribute__((noinline)) void
PROCESS_OVERRIDING_SYSTEM_DEFAULTS(uint64_t timeout)
{
	struct timespec ts;
	ts.tv_sec = timeout / NSEC_PER_SEC;
	ts.tv_nsec = timeout - ((long)ts.tv_sec * NSEC_PER_SEC);
	msleep((caddr_t)&sys_override_wait, &sys_override_lock, PRIBIO | PCATCH, "system_override", &ts);
}