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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int int64_t ;

/* Variables and functions */
 int esp_timer_get_time () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_measure(int64_t* sys_time, int64_t* real_time)
{
    struct timeval tv_time;
    int64_t t1, t2;
    do {
        t1 = esp_timer_get_time();
        gettimeofday(&tv_time, NULL);
        t2 = esp_timer_get_time();
    } while (t2 - t1 > 40);
    *real_time = t2;
    *sys_time = (int64_t)tv_time.tv_sec * 1000000L + tv_time.tv_usec;
}