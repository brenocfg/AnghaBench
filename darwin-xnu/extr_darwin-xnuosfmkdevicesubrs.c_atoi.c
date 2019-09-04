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

int
atoi(const char *cp)
{
        int     number;

        for (number = 0; ('0' <= *cp) && (*cp <= '9'); cp++)
                number = (number * 10) + (*cp - '0');

        return( number );
}