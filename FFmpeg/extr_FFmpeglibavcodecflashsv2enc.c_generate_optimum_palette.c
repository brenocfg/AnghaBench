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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  Palette ;

/* Variables and functions */

__attribute__((used)) static int generate_optimum_palette(Palette * palette, const uint8_t * image,
                                   int width, int height, int stride)
{
    //this isn't implemented yet!  Default palette only!
    return -1;
}