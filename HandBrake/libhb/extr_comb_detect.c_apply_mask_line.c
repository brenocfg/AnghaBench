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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static void apply_mask_line( uint8_t * srcp,
                             uint8_t * mskp,
                             int width )
{
    int x;

    for (x = 0; x < width; x++)
    {
        if (mskp[x] == 1)
        {
            srcp[x] = 255;
        }
        if (mskp[x] == 128)
        {
            srcp[x] = 128;
        }
    }
}