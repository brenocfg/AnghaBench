#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int Height; int Width; } ;
struct TYPE_7__ {int BufferSizeInKB; int BRCParamMultiplier; TYPE_1__ FrameInfo; } ;
struct TYPE_9__ {TYPE_2__ mfx; } ;
struct TYPE_8__ {int packet_size; TYPE_5__ param; int /*<<< orphan*/  session; } ;
typedef  TYPE_3__ QSVEncContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int MFXVideoENCODE_GetVideoParam (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int ff_qsv_print_error (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int qsv_retrieve_enc_jpeg_params(AVCodecContext *avctx, QSVEncContext *q)
{
    int ret = 0;

    ret = MFXVideoENCODE_GetVideoParam(q->session, &q->param);
    if (ret < 0)
        return ff_qsv_print_error(avctx, ret,
                                  "Error calling GetVideoParam");

    q->packet_size = q->param.mfx.BufferSizeInKB * q->param.mfx.BRCParamMultiplier * 1000;

    // for qsv mjpeg the return value maybe 0 so alloc the buffer
    if (q->packet_size == 0)
        q->packet_size = q->param.mfx.FrameInfo.Height * q->param.mfx.FrameInfo.Width * 4;

    return 0;
}