#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ frame_ct_out; int /*<<< orphan*/ * session; } ;
typedef  TYPE_2__ VTEncContext ;
struct TYPE_8__ {int /*<<< orphan*/  den; } ;
struct TYPE_10__ {scalar_t__ extradata_size; scalar_t__ extradata; TYPE_1__ time_base; TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/ * CVPixelBufferRef ;
typedef  int /*<<< orphan*/ * CVPixelBufferPoolRef ;
typedef  int /*<<< orphan*/  CMVideoCodecType ;
typedef  int /*<<< orphan*/  CMTime ;
typedef  int /*<<< orphan*/ * CMSampleBufferRef ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFNumberRef ;
typedef  int /*<<< orphan*/  CFDictionaryRef ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMTimeMake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CVPixelBufferPoolCreatePixelBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int VTCompressionSessionCompleteFrames (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VTCompressionSessionEncodeFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * VTCompressionSessionGetPixelBufferPool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kCMTimeIndefinite ; 
 int /*<<< orphan*/  kCMTimeInvalid ; 
 int kCVReturnSuccess ; 
 int vtenc_create_encoder (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int vtenc_q_pop (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vtenc_populate_extradata(AVCodecContext   *avctx,
                                    CMVideoCodecType codec_type,
                                    CFStringRef      profile_level,
                                    CFNumberRef      gamma_level,
                                    CFDictionaryRef  enc_info,
                                    CFDictionaryRef  pixel_buffer_info)
{
    VTEncContext *vtctx = avctx->priv_data;
    int status;
    CVPixelBufferPoolRef pool = NULL;
    CVPixelBufferRef pix_buf = NULL;
    CMTime time;
    CMSampleBufferRef buf = NULL;

    status = vtenc_create_encoder(avctx,
                                  codec_type,
                                  profile_level,
                                  gamma_level,
                                  enc_info,
                                  pixel_buffer_info,
                                  &vtctx->session);
    if (status)
        goto pe_cleanup;

    pool = VTCompressionSessionGetPixelBufferPool(vtctx->session);
    if(!pool){
        av_log(avctx, AV_LOG_ERROR, "Error getting pixel buffer pool.\n");
        goto pe_cleanup;
    }

    status = CVPixelBufferPoolCreatePixelBuffer(NULL,
                                                pool,
                                                &pix_buf);

    if(status != kCVReturnSuccess){
        av_log(avctx, AV_LOG_ERROR, "Error creating frame from pool: %d\n", status);
        goto pe_cleanup;
    }

    time = CMTimeMake(0, avctx->time_base.den);
    status = VTCompressionSessionEncodeFrame(vtctx->session,
                                             pix_buf,
                                             time,
                                             kCMTimeInvalid,
                                             NULL,
                                             NULL,
                                             NULL);

    if (status) {
        av_log(avctx,
               AV_LOG_ERROR,
               "Error sending frame for extradata: %d\n",
               status);

        goto pe_cleanup;
    }

    //Populates extradata - output frames are flushed and param sets are available.
    status = VTCompressionSessionCompleteFrames(vtctx->session,
                                                kCMTimeIndefinite);

    if (status)
        goto pe_cleanup;

    status = vtenc_q_pop(vtctx, 0, &buf, NULL);
    if (status) {
        av_log(avctx, AV_LOG_ERROR, "popping: %d\n", status);
        goto pe_cleanup;
    }

    CFRelease(buf);



pe_cleanup:
    if(vtctx->session)
        CFRelease(vtctx->session);

    vtctx->session = NULL;
    vtctx->frame_ct_out = 0;

    av_assert0(status != 0 || (avctx->extradata && avctx->extradata_size > 0));

    return status;
}