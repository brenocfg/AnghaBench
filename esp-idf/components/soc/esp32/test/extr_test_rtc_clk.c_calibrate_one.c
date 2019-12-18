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
typedef  int /*<<< orphan*/  rtc_cal_sel_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int rtc_clk_cal (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static uint32_t calibrate_one(rtc_cal_sel_t cal_clk, const char* name)
{
    const uint32_t cal_count = 1000;
    const float factor = (1 << 19) * 1000.0f;
    uint32_t cali_val;
    printf("%s:\n", name);
    for (int i = 0; i < 5; ++i) {
        printf("calibrate (%d): ", i);
        cali_val = rtc_clk_cal(cal_clk, cal_count);
        printf("%.3f kHz\n", factor / (float) cali_val);
    }
    return cali_val;
}