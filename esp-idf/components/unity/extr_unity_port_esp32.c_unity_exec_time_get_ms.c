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
typedef  int uint32_t ;

/* Variables and functions */
 int esp_clk_cpu_freq () ; 
 int s_test_start ; 
 int s_test_stop ; 

uint32_t unity_exec_time_get_ms(void)
{
    return (s_test_stop - s_test_start) / (esp_clk_cpu_freq() / 1000);
}