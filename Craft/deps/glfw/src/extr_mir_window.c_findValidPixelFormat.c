#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  connection; } ;
struct TYPE_4__ {TYPE_1__ mir; } ;
typedef  scalar_t__ MirPixelFormat ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  mir_connection_get_available_surface_formats (int /*<<< orphan*/ ,scalar_t__*,unsigned int,unsigned int*) ; 
 scalar_t__ mir_pixel_format_abgr_8888 ; 
 scalar_t__ mir_pixel_format_argb_8888 ; 
 scalar_t__ mir_pixel_format_invalid ; 
 scalar_t__ mir_pixel_format_xbgr_8888 ; 
 scalar_t__ mir_pixel_format_xrgb_8888 ; 
 int mir_pixel_formats ; 

__attribute__((used)) static MirPixelFormat findValidPixelFormat(void)
{
    unsigned int i, validFormats, mirPixelFormats = 32;
    MirPixelFormat formats[mir_pixel_formats];

    mir_connection_get_available_surface_formats(_glfw.mir.connection, formats,
                                                 mirPixelFormats, &validFormats);

    for (i = 0;  i < validFormats;  i++)
    {
        if (formats[i] == mir_pixel_format_abgr_8888 ||
            formats[i] == mir_pixel_format_xbgr_8888 ||
            formats[i] == mir_pixel_format_argb_8888 ||
            formats[i] == mir_pixel_format_xrgb_8888)
        {
            return formats[i];
        }
    }

    return mir_pixel_format_invalid;
}