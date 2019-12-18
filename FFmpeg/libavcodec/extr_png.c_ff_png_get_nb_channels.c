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
 int PNG_COLOR_MASK_ALPHA ; 
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COLOR_MASK_PALETTE ; 

int ff_png_get_nb_channels(int color_type)
{
    int channels;
    channels = 1;
    if ((color_type & (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_PALETTE)) ==
        PNG_COLOR_MASK_COLOR)
        channels = 3;
    if (color_type & PNG_COLOR_MASK_ALPHA)
        channels++;
    return channels;
}