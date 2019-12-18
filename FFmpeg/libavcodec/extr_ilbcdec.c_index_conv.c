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
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static void index_conv(int16_t *index)
{
    int k;

    for (k = 4; k < 6; k++) {
        if (index[k] >= 44 && index[k] < 108) {
            index[k] += 64;
        } else if (index[k] >= 108 && index[k] < 128) {
            index[k] += 128;
        }
    }
}