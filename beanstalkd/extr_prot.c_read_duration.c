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
typedef  scalar_t__ uint32 ;
typedef  int int64 ;

/* Variables and functions */
 int read_u32 (scalar_t__*,char const*,char**) ; 

__attribute__((used)) static int
read_duration(int64 *duration, const char *buf, char **end)
{
    int r;
    uint32 dur_sec;

    r = read_u32(&dur_sec, buf, end);
    if (r)
        return r;
    *duration = ((int64) dur_sec) * 1000000000;
    return 0;
}