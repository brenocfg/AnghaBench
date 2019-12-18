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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static void av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint8_t* cur_pos;

    for (cur_pos = counter + 7; cur_pos >= counter; cur_pos--) {
        (*cur_pos)++;
        if (*cur_pos != 0) {
            break;
        }
    }
}