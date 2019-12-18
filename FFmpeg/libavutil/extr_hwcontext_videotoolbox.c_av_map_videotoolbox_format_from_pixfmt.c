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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int /*<<< orphan*/  av_map_videotoolbox_format_from_pixfmt2 (int,int) ; 

uint32_t av_map_videotoolbox_format_from_pixfmt(enum AVPixelFormat pix_fmt)
{
    return av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}