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

/* Variables and functions */
 unsigned char* BASE_UUID ; 
 int LEN_UUID_128 ; 
 int LEN_UUID_16 ; 
 int LEN_UUID_32 ; 

int uuidType(unsigned char *p_uuid)
{
    int i = 0;
    int match = 0;
    int all_zero = 1;

    for (i = 0; i != 16; ++i) {
        if (i == 12 || i == 13) {
            continue;
        }

        if (p_uuid[i] == BASE_UUID[i]) {
            ++match;
        }

        if (p_uuid[i] != 0) {
            all_zero = 0;
        }
    }
    if (all_zero) {
        return 0;
    }
    if (match == 12) {
        return LEN_UUID_32;
    }
    if (match == 14) {
        return LEN_UUID_16;
    }
    return LEN_UUID_128;
}