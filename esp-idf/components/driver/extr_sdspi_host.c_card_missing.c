#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ gpio_cd; } ;

/* Variables and functions */
 scalar_t__ GPIO_UNUSED ; 
 int gpio_get_level (scalar_t__) ; 
 TYPE_1__* s_slots ; 

__attribute__((used)) static bool card_missing(int slot)
{
    if (s_slots[slot].gpio_cd == GPIO_UNUSED) {
        return false;
    }
    return gpio_get_level(s_slots[slot].gpio_cd) == 1;
}