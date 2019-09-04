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
 int FF_ARRAY_ELEMS (int const*) ; 

__attribute__((used)) static int check_fps(int fps)
{
    int i;
    static const int supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    for (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        if (fps == supported_fps[i])
            return 0;
    return -1;
}