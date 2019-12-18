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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int /*<<< orphan*/  linesize; scalar_t__ data; } ;
typedef  TYPE_1__ AVPicture ;

/* Variables and functions */
 int av_image_copy_to_buffer (unsigned char*,int,int /*<<< orphan*/  const* const*,int /*<<< orphan*/ ,int,int,int,int) ; 

int avpicture_layout(const AVPicture* src, enum AVPixelFormat pix_fmt, int width, int height,
                     unsigned char *dest, int dest_size)
{
    return av_image_copy_to_buffer(dest, dest_size,
                                   (const uint8_t * const*)src->data, src->linesize,
                                   pix_fmt, width, height, 1);
}