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
struct TYPE_4__ {int coded_width; int coded_height; int /*<<< orphan*/  lowres; void* height; void* width; int /*<<< orphan*/  max_pixels; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 void* AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PIX_FMT_NONE ; 
 int av_image_check_size2 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

int ff_set_dimensions(AVCodecContext *s, int width, int height)
{
    int ret = av_image_check_size2(width, height, s->max_pixels, AV_PIX_FMT_NONE, 0, s);

    if (ret < 0)
        width = height = 0;

    s->coded_width  = width;
    s->coded_height = height;
    s->width        = AV_CEIL_RSHIFT(width,  s->lowres);
    s->height       = AV_CEIL_RSHIFT(height, s->lowres);

    return ret;
}