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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int av_image_get_buffer_size (int,int,int,int) ; 

int avpicture_get_size(enum AVPixelFormat pix_fmt, int width, int height)
{
    return av_image_get_buffer_size(pix_fmt, width, height, 1);
}