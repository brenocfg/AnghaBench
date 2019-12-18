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
typedef  scalar_t__ DWORD ;

/* Variables and functions */

DWORD multiprecision_add(DWORD *c, DWORD *a, DWORD *b, uint32_t keyLength)
{
    DWORD carrier;
    DWORD temp;

    carrier = 0;
    for (uint32_t i = 0; i < keyLength; i++) {
        temp = a[i] + carrier;
        carrier = (temp < carrier);
        temp += b[i];
        carrier |= (temp < b[i]);
        c[i] = temp;
    }

    return carrier;
}