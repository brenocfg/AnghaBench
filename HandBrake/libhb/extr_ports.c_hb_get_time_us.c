#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {int QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (TYPE_1__*) ; 
 int /*<<< orphan*/  QueryPerformanceFrequency (TYPE_1__*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

uint64_t hb_get_time_us()
{
#ifdef SYS_MINGW
    static LARGE_INTEGER frequency;
    LARGE_INTEGER cur_time;

    if (frequency.QuadPart == 0)
    {
          QueryPerformanceFrequency(&frequency);
    }

    QueryPerformanceCounter(&cur_time);

    return (uint64_t)(1000000 * cur_time.QuadPart / frequency.QuadPart);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((uint64_t)tv.tv_sec * 1000000 + (uint64_t)tv.tv_usec);
#endif
}