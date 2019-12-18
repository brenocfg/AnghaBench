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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_SetAlarm (int /*<<< orphan*/ ,struct timespec const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dvd_timeoutalarm ; 
 int /*<<< orphan*/  __dvd_timeouthandler ; 

__attribute__((used)) static void __SetupTimeoutAlarm(const struct timespec *tp)
{
	SYS_SetAlarm(__dvd_timeoutalarm,tp,__dvd_timeouthandler,NULL);
}