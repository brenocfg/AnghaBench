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
typedef  char uint8_t ;

/* Variables and functions */

__attribute__((used)) static int _mdns_txt_item_name_get_len(const uint8_t * data, size_t len)
{
    int i;
    if (*data == '=') {
        return -1;
    }
    for (i = 0; i < len; i++) {
        if (data[i] == '=') {
            return i;
        }
    }
    return len;
}