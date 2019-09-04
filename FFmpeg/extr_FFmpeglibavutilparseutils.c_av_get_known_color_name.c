#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {char const* name; int /*<<< orphan*/ * rgb_color; } ;
typedef  TYPE_1__ ColorEntry ;

/* Variables and functions */
 unsigned int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* color_table ; 

const char *av_get_known_color_name(int color_idx, const uint8_t **rgbp)
{
    const ColorEntry *color;

    if ((unsigned)color_idx >= FF_ARRAY_ELEMS(color_table))
        return NULL;

    color = &color_table[color_idx];
    if (rgbp)
        *rgbp = color->rgb_color;

    return color->name;
}