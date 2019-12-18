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
typedef  int /*<<< orphan*/  TimerHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int volatile*,int volatile) ; 
 scalar_t__ pvTimerGetTimerID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_callback(TimerHandle_t timer)
{
    volatile int *count;
    count = (volatile int *)pvTimerGetTimerID( timer );
    (*count)++;
    printf("Callback timer %p count %p = %d\n", timer, count, *count);
}