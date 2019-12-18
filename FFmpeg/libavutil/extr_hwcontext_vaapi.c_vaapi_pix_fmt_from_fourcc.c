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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int pix_fmt; } ;
typedef  TYPE_1__ VAAPIFormatDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 TYPE_1__* vaapi_format_from_fourcc (unsigned int) ; 

__attribute__((used)) static enum AVPixelFormat vaapi_pix_fmt_from_fourcc(unsigned int fourcc)
{
    const VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    if (desc)
        return desc->pix_fmt;
    else
        return AV_PIX_FMT_NONE;
}