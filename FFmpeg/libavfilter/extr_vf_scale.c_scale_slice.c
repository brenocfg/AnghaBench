#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct SwsContext {int dummy; } ;
struct TYPE_11__ {TYPE_1__* dst; } ;
struct TYPE_10__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_9__ {int vsub; scalar_t__ output_is_pal; scalar_t__ input_is_pal; } ;
struct TYPE_8__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ ScaleContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 int sws_scale (struct SwsContext*,int /*<<< orphan*/  const**,int*,int,int,int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static int scale_slice(AVFilterLink *link, AVFrame *out_buf, AVFrame *cur_pic, struct SwsContext *sws, int y, int h, int mul, int field)
{
    ScaleContext *scale = link->dst->priv;
    const uint8_t *in[4];
    uint8_t *out[4];
    int in_stride[4],out_stride[4];
    int i;

    for (i=0; i<4; i++) {
        int vsub= ((i+1)&2) ? scale->vsub : 0;
         in_stride[i] = cur_pic->linesize[i] * mul;
        out_stride[i] = out_buf->linesize[i] * mul;
         in[i] = cur_pic->data[i] + ((y>>vsub)+field) * cur_pic->linesize[i];
        out[i] = out_buf->data[i] +            field  * out_buf->linesize[i];
    }
    if (scale->input_is_pal)
         in[1] = cur_pic->data[1];
    if (scale->output_is_pal)
        out[1] = out_buf->data[1];

    return sws_scale(sws, in, in_stride, y/mul, h,
                         out,out_stride);
}