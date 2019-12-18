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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */

void multiprecision_copy(DWORD *c, DWORD *a, uint32_t keyLength)
{
    for (uint32_t i = 0; i < keyLength; i++) {
        c[i] = a[i];
    }
}