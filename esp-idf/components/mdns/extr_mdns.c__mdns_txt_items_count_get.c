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
typedef  size_t uint8_t ;
typedef  size_t uint16_t ;

/* Variables and functions */

__attribute__((used)) static int _mdns_txt_items_count_get(const uint8_t * data, size_t len)
{
    if (len == 1) {
        return 0;
    }

    int num_items = 0;
    uint16_t i=0;
    size_t partLen = 0;

    while (i < len) {
        partLen = data[i++];
        if (!partLen) {
            break;
        }
        if ((i+partLen) > len) {
            return -1;//error
        }
        i+=partLen;
        num_items++;
    }
    return num_items;
}