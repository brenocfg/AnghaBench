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
typedef  size_t uint32_t ;
typedef  size_t DWORD ;

/* Variables and functions */
 int DWORD_BITS ; 

DWORD multiprecision_lshift(DWORD *c, DWORD *a, uint32_t keyLength)
{
    int j;
    uint32_t b = 1;
    j = DWORD_BITS - b;

    DWORD carrier = 0;
    DWORD temp;

    for (uint32_t i = 0; i < keyLength; i++) {
        temp = a[i];  // in case c==a
        c[i] = (temp << b) | carrier;
        carrier = temp >> j;
    }

    return carrier;
}