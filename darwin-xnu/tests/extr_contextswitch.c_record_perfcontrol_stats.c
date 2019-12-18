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
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  T_PERF (char const*,int,char const*,char const*) ; 
 int /*<<< orphan*/  sysctlbyname (char const*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void record_perfcontrol_stats(const char *sysctlname, const char *units, const char *info)
{
    int data = 0;
    size_t data_size = sizeof(data);
    T_ASSERT_POSIX_ZERO(sysctlbyname(sysctlname,
	    &data, &data_size, NULL, 0), 
	    "%s", sysctlname);
    T_PERF(info, data, units, info);
}