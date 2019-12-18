#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  error_code; int /*<<< orphan*/  writer; TYPE_2__* custom_ptr; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_20__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  size; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ WebPMemoryWriter ;
struct TYPE_23__ {TYPE_3__* priv_data; } ;
struct TYPE_22__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  data; } ;
struct TYPE_21__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_3__ LibWebPContext ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int WebPEncode (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  WebPMemoryWrite ; 
 int /*<<< orphan*/  WebPMemoryWriterClear (TYPE_2__*) ; 
 int /*<<< orphan*/  WebPMemoryWriterInit (TYPE_2__*) ; 
 int /*<<< orphan*/  WebPPictureFree (TYPE_1__*) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ff_alloc_packet2 (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_libwebp_error_to_averror (int /*<<< orphan*/ ) ; 
 int ff_libwebp_get_frame (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,TYPE_1__**) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libwebp_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                                const AVFrame *frame, int *got_packet)
{
    LibWebPContext *s  = avctx->priv_data;
    WebPPicture *pic = NULL;
    AVFrame *alt_frame = NULL;
    WebPMemoryWriter mw = { 0 };

    int ret = ff_libwebp_get_frame(avctx, s, frame, &alt_frame, &pic);
    if (ret < 0)
        goto end;

    WebPMemoryWriterInit(&mw);
    pic->custom_ptr = &mw;
    pic->writer     = WebPMemoryWrite;

    ret = WebPEncode(&s->config, pic);
    if (!ret) {
        av_log(avctx, AV_LOG_ERROR, "WebPEncode() failed with error: %d\n",
               pic->error_code);
        ret = ff_libwebp_error_to_averror(pic->error_code);
        goto end;
    }

    ret = ff_alloc_packet2(avctx, pkt, mw.size, mw.size);
    if (ret < 0)
        goto end;
    memcpy(pkt->data, mw.mem, mw.size);

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

end:
#if (WEBP_ENCODER_ABI_VERSION > 0x0203)
    WebPMemoryWriterClear(&mw);
#else
    free(mw.mem); /* must use free() according to libwebp documentation */
#endif
    WebPPictureFree(pic);
    av_freep(&pic);
    av_frame_free(&alt_frame);

    return ret;
}