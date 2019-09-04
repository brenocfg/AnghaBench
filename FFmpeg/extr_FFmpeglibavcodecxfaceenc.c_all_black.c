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
 int XFACE_WIDTH ; 

__attribute__((used)) static int all_black(char *bitmap, int w, int h)
{
    if (w > 3) {
        w /= 2;
        h /= 2;
        return (all_black(bitmap, w, h) && all_black(bitmap + w, w, h) &&
                all_black(bitmap + XFACE_WIDTH * h, w, h) &&
                all_black(bitmap + XFACE_WIDTH * h + w, w, h));
    } else {
        /* at least one pixel in the 2x2 grid is non-zero */
        return *bitmap || *(bitmap + 1) ||
               *(bitmap + XFACE_WIDTH) || *(bitmap + XFACE_WIDTH + 1);
    }
}