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

__attribute__((used)) static int
rounddown10(int n)
{
    int tens = 0;
    /* tens = floor(log_10(n)) */
    while (n >= 10) {
        n = n / 10;
        tens++;
    }
    /* result = 10**tens */
    int i, result = 1;
    for (i = 0; i < tens; i++) {
        result *= 10;
    }
    return result;
}