#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  fmt; } ;
struct TYPE_9__ {TYPE_2__* plane; TYPE_1__ f; } ;
typedef  TYPE_3__ hb_buffer_t ;
struct TYPE_10__ {int log2_chroma_w; int log2_chroma_h; } ;
struct TYPE_8__ {int stride; int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ AVPixFmtDescriptor ;

/* Variables and functions */
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

int hb_picture_crop(uint8_t *data[], int stride[], hb_buffer_t *buf,
                    int top, int left)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(buf->f.fmt);
    int x_shift, y_shift;

    if (desc == NULL)
        return -1;

    x_shift = desc->log2_chroma_w;
    y_shift = desc->log2_chroma_h;

    data[0] = buf->plane[0].data + top * buf->plane[0].stride + left;
    data[1] = buf->plane[1].data + (top >> y_shift) * buf->plane[1].stride +
              (left >> x_shift);
    data[2] = buf->plane[2].data + (top >> y_shift) * buf->plane[2].stride +
              (left >> x_shift);
    data[3] = NULL;

    stride[0] = buf->plane[0].stride;
    stride[1] = buf->plane[1].stride;
    stride[2] = buf->plane[2].stride;
    stride[3] = 0;

    return 0;
}