#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_6__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_5__ {int /*<<< orphan*/  imageData; int /*<<< orphan*/  widthStep; } ;
typedef  TYPE_1__ IplImage ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void fill_frame_from_iplimage(AVFrame *frame, const IplImage *img, enum AVPixelFormat pixfmt)
{
    frame->linesize[0] = img->widthStep;
    frame->data[0]     = img->imageData;
}