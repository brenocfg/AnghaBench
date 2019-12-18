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
 int rounddown10 (int) ; 

__attribute__((used)) static int
roundup(int n)
{
    int base = rounddown10(n);
    if (n <= base)
        return base;
    if (n <= 2*base)
        return 2*base;
    if (n <= 3*base)
        return 3*base;
    if (n <= 5*base)
        return 5*base;
    return 10*base;
}