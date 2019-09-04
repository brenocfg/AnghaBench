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
 int ff_sqrt (unsigned int) ; 

int ff_t_sqrt(unsigned int x)
{
    int s = 2;
    while (x > 0xfff) {
        s++;
        x >>= 2;
    }

    return ff_sqrt(x << 20) << s;
}