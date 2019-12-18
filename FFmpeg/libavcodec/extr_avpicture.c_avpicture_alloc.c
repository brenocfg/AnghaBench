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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_4__ {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPicture ;

/* Variables and functions */
 int av_image_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int avpicture_alloc(AVPicture *picture,
                    enum AVPixelFormat pix_fmt, int width, int height)
{
    int ret = av_image_alloc(picture->data, picture->linesize,
                             width, height, pix_fmt, 1);
    if (ret < 0) {
        memset(picture, 0, sizeof(AVPicture));
        return ret;
    }

    return 0;
}