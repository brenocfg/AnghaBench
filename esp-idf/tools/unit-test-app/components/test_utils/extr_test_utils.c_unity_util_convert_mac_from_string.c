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

/* Variables and functions */
 int strtol (char const*,char**,int) ; 

bool unity_util_convert_mac_from_string(const char* mac_str, uint8_t *mac_addr)
{
    uint8_t loop = 0;
    uint8_t tmp = 0;
    const char *start;
    char *stop;

    for (loop = 0; loop < 6; loop++) {
        start = mac_str + loop * 3;
        tmp = strtol(start, &stop, 16);
        if (stop - start == 2 && (*stop == ':' || (*stop == 0 && loop == 5))) {
            mac_addr[loop] = tmp;
        } else {
            return false;
        }
    }
    return true;
}