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
typedef  int UINT32 ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */

UINT32 multiprecision_most_signdwords(DWORD *a, uint32_t keyLength)
{
    int  i;
    for (i = keyLength - 1; i >= 0; i--)
        if (a[i]) {
            break;
        }
    return (i + 1);
}