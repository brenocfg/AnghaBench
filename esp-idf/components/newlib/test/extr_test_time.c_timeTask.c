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
typedef  int /*<<< orphan*/  xSemaphoreHandle ;
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int exit_flag ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  settimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timeTask(void *pvParameters)
{
    xSemaphoreHandle *sema = (xSemaphoreHandle *) pvParameters;
    struct timeval tv_time = { .tv_sec = 1520000000, .tv_usec = 900000 };

    // although exit flag is set in another task, checking (exit_flag == false) is safe
    while (exit_flag == false) {
        tv_time.tv_sec += 1;
        settimeofday(&tv_time, NULL);
        gettimeofday(&tv_time, NULL);
    }
    xSemaphoreGive(*sema);
    vTaskDelete(NULL);
}