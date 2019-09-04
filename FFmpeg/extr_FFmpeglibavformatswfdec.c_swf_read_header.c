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
struct TYPE_6__ {int /*<<< orphan*/  ctx_flags; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {scalar_t__ samples_per_frame; int /*<<< orphan*/  frame_rate; } ;
typedef  TYPE_1__ SWFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVFMTCTX_NOHEADER ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  EIO ; 
 int MKBETAG (float,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int swf_read_header(AVFormatContext *s)
{
    SWFContext *swf = s->priv_data;
    AVIOContext *pb = s->pb;
    int nbits, len, tag;

    tag = avio_rb32(pb) & 0xffffff00;
    avio_rl32(pb);

    if (tag == MKBETAG('C', 'W', 'S', 0)) {
        av_log(s, AV_LOG_INFO, "SWF compressed file detected\n");
#if CONFIG_ZLIB
        swf->zbuf_in  = av_malloc(ZBUF_SIZE);
        swf->zbuf_out = av_malloc(ZBUF_SIZE);
        swf->zpb = avio_alloc_context(swf->zbuf_out, ZBUF_SIZE, 0, s,
                                      zlib_refill, NULL, NULL);
        if (!swf->zbuf_in || !swf->zbuf_out || !swf->zpb)
            return AVERROR(ENOMEM);
        swf->zpb->seekable = 0;
        if (inflateInit(&swf->zstream) != Z_OK) {
            av_log(s, AV_LOG_ERROR, "Unable to init zlib context\n");
            return AVERROR(EINVAL);
        }
        pb = swf->zpb;
#else
        av_log(s, AV_LOG_ERROR, "zlib support is required to read SWF compressed files\n");
        return AVERROR(EIO);
#endif
    } else if (tag != MKBETAG('F', 'W', 'S', 0))
        return AVERROR(EIO);
    /* skip rectangle size */
    nbits = avio_r8(pb) >> 3;
    len = (4 * nbits - 3 + 7) / 8;
    avio_skip(pb, len);
    swf->frame_rate = avio_rl16(pb); /* 8.8 fixed */
    avio_rl16(pb); /* frame count */

    swf->samples_per_frame = 0;
    s->ctx_flags |= AVFMTCTX_NOHEADER;
    return 0;
}