#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int max_plane; int /*<<< orphan*/  fmt; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  data; TYPE_2__* plane; TYPE_1__ f; } ;
typedef  TYPE_3__ hb_buffer_t ;
struct TYPE_6__ {int stride; int /*<<< orphan*/  height_stride; } ;

/* Variables and functions */
 int av_image_fill_pointers (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hb_error (char*,int,int) ; 

int hb_picture_fill(uint8_t *data[], int stride[], hb_buffer_t *buf)
{
    int ret, ii;

    for (ii = 0; ii <= buf->f.max_plane; ii++)
        stride[ii] = buf->plane[ii].stride;
    for (; ii < 4; ii++)
        stride[ii] = stride[ii - 1];

    ret = av_image_fill_pointers(data, buf->f.fmt,
                                 buf->plane[0].height_stride,
                                 buf->data, stride);
    if (ret != buf->size)
    {
        hb_error("Internal error hb_picture_fill expected %d, got %d",
                 buf->size, ret);
    }
    return ret;
}