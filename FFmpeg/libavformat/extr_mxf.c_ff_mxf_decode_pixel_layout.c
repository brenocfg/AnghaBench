#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_2__ {int pix_fmt; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 TYPE_1__* ff_mxf_pixel_layouts ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int num_pixel_layouts ; 

int ff_mxf_decode_pixel_layout(const char pixel_layout[16], enum AVPixelFormat *pix_fmt)
{
    int x;

    for(x = 0; x < num_pixel_layouts; x++) {
        if (!memcmp(pixel_layout, ff_mxf_pixel_layouts[x].data, 16)) {
            *pix_fmt = ff_mxf_pixel_layouts[x].pix_fmt;
            return 0;
        }
    }

    return -1;
}