#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVFrameSideDataType { ____Placeholder_AVFrameSideDataType } AVFrameSideDataType ;
struct TYPE_12__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int nb_side_data; TYPE_1__** side_data; } ;
struct TYPE_10__ {int type; int /*<<< orphan*/  size; TYPE_3__* buf; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVFrameSideData ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVBufferRef ;

/* Variables and functions */
 int INT_MAX ; 
 TYPE_1__* av_mallocz (int) ; 
 TYPE_1__** av_realloc (TYPE_1__**,int) ; 

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 enum AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    AVFrameSideData *ret, **tmp;

    if (!buf)
        return NULL;

    if (frame->nb_side_data > INT_MAX / sizeof(*frame->side_data) - 1)
        return NULL;

    tmp = av_realloc(frame->side_data,
                     (frame->nb_side_data + 1) * sizeof(*frame->side_data));
    if (!tmp)
        return NULL;
    frame->side_data = tmp;

    ret = av_mallocz(sizeof(*ret));
    if (!ret)
        return NULL;

    ret->buf = buf;
    ret->data = ret->buf->data;
    ret->size = buf->size;
    ret->type = type;

    frame->side_data[frame->nb_side_data++] = ret;

    return ret;
}