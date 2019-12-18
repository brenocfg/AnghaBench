#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int buttons_count; scalar_t__ buttons; } ;
typedef  TYPE_1__ joydata_t ;

/* Variables and functions */
 int joy_read_element (TYPE_1__*,scalar_t__) ; 

int joy_read_button(joydata_t *joy, int num)  {
    /* Subtract 1 from the number to get the index. */
    --num;

    if(num >= joy->buttons_count) {
        return -1;
    }

    return joy_read_element(joy, joy->buttons + num);
}