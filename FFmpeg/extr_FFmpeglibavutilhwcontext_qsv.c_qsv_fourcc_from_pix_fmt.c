#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int pix_fmt; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* supported_pixel_formats ; 

__attribute__((used)) static uint32_t qsv_fourcc_from_pix_fmt(enum AVPixelFormat pix_fmt)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        if (supported_pixel_formats[i].pix_fmt == pix_fmt)
            return supported_pixel_formats[i].fourcc;
    }
    return 0;
}