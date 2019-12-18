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

/* Variables and functions */
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int) ; 
 int rate ; 
 int /*<<< orphan*/  wakeups_per_second ; 

__attribute__((used)) static void dac_audio_set_rate(void)
{
	wakeups_per_second = ktime_set(0, 1000000000 / rate);
}