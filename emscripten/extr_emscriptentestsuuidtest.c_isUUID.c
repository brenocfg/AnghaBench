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
 scalar_t__ islower (char) ; 
 scalar_t__ isupper (char) ; 
 scalar_t__ isxdigit (char) ; 

int isUUID(char* p, int upper) {
    char* p1 = p;
    do {
        if (!(isxdigit(*p1) || (*p1 == '-')) || (upper && islower(*p1)) || (!upper && isupper(*p1))) {
            return 0;
        } else {
        }
    } while (*++p1 != 0);

    if ((p[8] == '-') && (p[13] == '-') && (p[18] == '-') && (p[23] == '-')) {
        return 1;
    } else {
        return 0;
    }   
}