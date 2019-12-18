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
typedef  int uint32_t ;
typedef  int DWORD ;

/* Variables and functions */
 int DWORD_BITS ; 

void multiprecision_rshift(DWORD *c, DWORD *a, uint32_t keyLength)
{
    int j;
    DWORD b = 1;

    j = DWORD_BITS - b;

    DWORD carrier = 0;
    DWORD temp;
    for (int i = keyLength - 1; i >= 0; i--) {
        temp = a[i]; // in case of c==a
        c[i] = (temp >> b) | carrier;
        carrier = temp << j;
    }
}