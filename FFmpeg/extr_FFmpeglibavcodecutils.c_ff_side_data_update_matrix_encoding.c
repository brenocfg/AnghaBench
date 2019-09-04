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
typedef  enum AVMatrixEncoding { ____Placeholder_AVMatrixEncoding } AVMatrixEncoding ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ AVFrameSideData ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_FRAME_DATA_MATRIXENCODING ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* av_frame_get_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* av_frame_new_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int ff_side_data_update_matrix_encoding(AVFrame *frame,
                                        enum AVMatrixEncoding matrix_encoding)
{
    AVFrameSideData *side_data;
    enum AVMatrixEncoding *data;

    side_data = av_frame_get_side_data(frame, AV_FRAME_DATA_MATRIXENCODING);
    if (!side_data)
        side_data = av_frame_new_side_data(frame, AV_FRAME_DATA_MATRIXENCODING,
                                           sizeof(enum AVMatrixEncoding));

    if (!side_data)
        return AVERROR(ENOMEM);

    data  = (enum AVMatrixEncoding*)side_data->data;
    *data = matrix_encoding;

    return 0;
}