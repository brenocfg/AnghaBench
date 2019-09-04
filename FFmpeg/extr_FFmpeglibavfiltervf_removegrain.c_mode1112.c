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

__attribute__((used)) static int mode1112(int c, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    const int sum = 4 * c + 2 * (a2 + a4 + a5 + a7) + a1 + a3 + a6 + a8;
    const int val = (sum + 8) >> 4;

    return val;
}