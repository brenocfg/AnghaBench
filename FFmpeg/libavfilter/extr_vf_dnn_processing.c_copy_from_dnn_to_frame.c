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
typedef  float uint8_t ;
struct TYPE_6__ {scalar_t__ format; int height; int width; int* linesize; float** data; } ;
struct TYPE_5__ {scalar_t__ dt; float* data; } ;
typedef  TYPE_1__ DNNData ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_BGR24 ; 
 scalar_t__ AV_PIX_FMT_RGB24 ; 
 scalar_t__ DNN_FLOAT ; 
 scalar_t__ DNN_UINT8 ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 float av_clip_uintp2 (int,int) ; 

__attribute__((used)) static int copy_from_dnn_to_frame(AVFrame *out, const DNNData *dnn_data)
{
    // extend this function to support more formats
    av_assert0(out->format == AV_PIX_FMT_RGB24 || out->format == AV_PIX_FMT_BGR24);

    if (dnn_data->dt == DNN_FLOAT) {
        float *dnn_output = dnn_data->data;
        for (int i = 0; i < out->height; i++) {
            for(int j = 0; j < out->width * 3; j++) {
                int k = i * out->linesize[0] + j;
                int t = i * out->width * 3 + j;
                out->data[0][k] = av_clip_uintp2((int)(dnn_output[t] * 255.0f), 8);
            }
        }
    } else {
        uint8_t *dnn_output = dnn_data->data;
        av_assert0(dnn_data->dt == DNN_UINT8);
        for (int i = 0; i < out->height; i++) {
            for(int j = 0; j < out->width * 3; j++) {
                int k = i * out->linesize[0] + j;
                int t = i * out->width * 3 + j;
                out->data[0][k] = dnn_output[t];
            }
        }
    }

    return 0;
}