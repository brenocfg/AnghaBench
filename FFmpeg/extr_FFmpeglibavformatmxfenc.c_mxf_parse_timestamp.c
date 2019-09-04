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
typedef  int uint64_t ;
typedef  int time_t ;
struct tm {int tm_hour; int tm_min; int tm_sec; scalar_t__ tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  int int64_t ;

/* Variables and functions */
 struct tm* gmtime_r (int*,struct tm*) ; 

__attribute__((used)) static uint64_t mxf_parse_timestamp(int64_t timestamp64)
{
    time_t timestamp = timestamp64 / 1000000;
    struct tm tmbuf;
    struct tm *time = gmtime_r(&timestamp, &tmbuf);
    if (!time)
        return 0;
    return (uint64_t)(time->tm_year+1900) << 48 |
           (uint64_t)(time->tm_mon+1)     << 40 |
           (uint64_t) time->tm_mday       << 32 |
                      time->tm_hour       << 24 |
                      time->tm_min        << 16 |
                      time->tm_sec        << 8  |
                      (timestamp64 % 1000000) / 4000;
}