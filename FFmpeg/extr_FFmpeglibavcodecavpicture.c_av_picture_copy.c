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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_4__ {int /*<<< orphan*/  linesize; scalar_t__ data; } ;
typedef  TYPE_1__ AVPicture ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int,int,int) ; 

void av_picture_copy(AVPicture *dst, const AVPicture *src,
                     enum AVPixelFormat pix_fmt, int width, int height)
{
    av_image_copy(dst->data, dst->linesize, (const uint8_t **)src->data,
                  src->linesize, pix_fmt, width, height);
}