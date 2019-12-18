#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ bit_count; } ;
typedef  TYPE_1__ esp_efuse_desc_t ;

/* Variables and functions */

int esp_efuse_get_field_size(const esp_efuse_desc_t* field[])
{
    int bits_counter = 0;
    if (field != NULL) {
        int i = 0;
        while (field[i] != NULL) {
            bits_counter += field[i]->bit_count;
            ++i;
        }
    }
    return bits_counter;
}