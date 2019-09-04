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
struct TYPE_3__ {scalar_t__ pix_fmt; unsigned int fourcc; } ;
typedef  TYPE_1__ PixelFormatTag ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 

enum AVPixelFormat avpriv_find_pix_fmt(const PixelFormatTag *tags,
                                       unsigned int fourcc)
{
    while (tags->pix_fmt >= 0) {
        if (tags->fourcc == fourcc)
            return tags->pix_fmt;
        tags++;
    }
    return AV_PIX_FMT_NONE;
}