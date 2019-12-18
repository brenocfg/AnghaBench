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
typedef  int u8_t ;
typedef  int u16_t ;

/* Variables and functions */

__attribute__((used)) static u16_t hb_pwr2(u8_t val, u8_t sub)
{
    if (!val) {
        return 0x0000;
    } else if (val == 0xff || val == 0x11) {
        return 0xffff;
    } else {
        return (1 << (val - sub));
    }
}