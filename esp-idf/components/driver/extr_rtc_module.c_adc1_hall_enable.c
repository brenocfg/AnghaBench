#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int xpd_hall; } ;
struct TYPE_4__ {TYPE_1__ hall_sens; } ;

/* Variables and functions */
 TYPE_2__ RTCIO ; 

__attribute__((used)) static inline void adc1_hall_enable(bool enable)
{
#if CONFIG_IDF_TARGET_ESP32
    RTCIO.hall_sens.xpd_hall = enable;
#endif
}