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
typedef  int uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int rand () ; 

__attribute__((used)) static int32_t bt_app_a2d_data_cb(uint8_t *data, int32_t len)
{
    if (len < 0 || data == NULL) {
        return 0;
    }

    // generate random sequence
    int val = rand() % (1 << 16);
    for (int i = 0; i < (len >> 1); i++) {
        data[(i << 1)] = val & 0xff;
        data[(i << 1) + 1] = (val >> 8) & 0xff;
    }

    return len;
}