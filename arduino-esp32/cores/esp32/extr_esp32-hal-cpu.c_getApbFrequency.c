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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  rtc_cpu_freq_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  calculateApb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_get_config (int /*<<< orphan*/ *) ; 

uint32_t getApbFrequency(){
    rtc_cpu_freq_config_t conf;
    rtc_clk_cpu_freq_get_config(&conf);
    return calculateApb(&conf);
}