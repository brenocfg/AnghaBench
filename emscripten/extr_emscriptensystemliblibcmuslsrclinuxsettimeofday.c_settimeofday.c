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
struct timezone {int dummy; } ;
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_settimeofday ; 
 int syscall (int /*<<< orphan*/ ,struct timeval const*,int /*<<< orphan*/ ) ; 

int settimeofday(const struct timeval *tv, const struct timezone *tz)
{
	return syscall(SYS_settimeofday, tv, 0);
}