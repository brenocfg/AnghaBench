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
typedef  scalar_t__ gint ;
typedef  char gchar ;
typedef  scalar_t__ gboolean ;

/* Variables and functions */
 scalar_t__ HB_PRESET_TYPE_CUSTOM ; 

__attribute__((used)) static const gchar*
get_preset_color(gint type, gboolean is_folder)
{
    const gchar *color;

    if (type == HB_PRESET_TYPE_CUSTOM)
    {
        color = "DimGray";
        if (is_folder)
        {
            color = "black";
        }
    }
    else
    {
        color = "blue";
        if (is_folder)
        {
            color = "Navy";
        }
    }
    return color;
}