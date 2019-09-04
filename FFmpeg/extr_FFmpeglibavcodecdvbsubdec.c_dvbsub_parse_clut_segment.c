#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_13__ {scalar_t__ strict_std_compliance; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int id; int version; void** clut256; void** clut16; void** clut4; struct TYPE_12__* next; } ;
struct TYPE_11__ {TYPE_2__* clut_list; } ;
typedef  TYPE_1__ DVBSubContext ;
typedef  TYPE_2__ DVBSubCLUT ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FF_COMPLIANCE_NORMAL ; 
 void* RGBA (int,int,int,int) ; 
 int /*<<< orphan*/  YUV_TO_RGB1_CCIR (int,int) ; 
 int /*<<< orphan*/  YUV_TO_RGB2_CCIR (int,int,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int const) ; 
 TYPE_2__* av_malloc (int) ; 
 int /*<<< orphan*/  default_clut ; 
 int /*<<< orphan*/  ff_dlog (TYPE_3__*,char*,...) ; 
 TYPE_2__* get_clut (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dvbsub_parse_clut_segment(AVCodecContext *avctx,
                                     const uint8_t *buf, int buf_size)
{
    DVBSubContext *ctx = avctx->priv_data;

    const uint8_t *buf_end = buf + buf_size;
    int i, clut_id;
    int version;
    DVBSubCLUT *clut;
    int entry_id, depth , full_range;
    int y, cr, cb, alpha;
    int r, g, b, r_add, g_add, b_add;

    ff_dlog(avctx, "DVB clut packet:\n");

    for (i=0; i < buf_size; i++) {
        ff_dlog(avctx, "%02x ", buf[i]);
        if (i % 16 == 15)
            ff_dlog(avctx, "\n");
    }

    if (i % 16)
        ff_dlog(avctx, "\n");

    clut_id = *buf++;
    version = ((*buf)>>4)&15;
    buf += 1;

    clut = get_clut(ctx, clut_id);

    if (!clut) {
        clut = av_malloc(sizeof(DVBSubCLUT));
        if (!clut)
            return AVERROR(ENOMEM);

        memcpy(clut, &default_clut, sizeof(DVBSubCLUT));

        clut->id = clut_id;
        clut->version = -1;

        clut->next = ctx->clut_list;
        ctx->clut_list = clut;
    }

    if (clut->version != version) {

    clut->version = version;

    while (buf + 4 < buf_end) {
        entry_id = *buf++;

        depth = (*buf) & 0xe0;

        if (depth == 0) {
            av_log(avctx, AV_LOG_ERROR, "Invalid clut depth 0x%x!\n", *buf);
        }

        full_range = (*buf++) & 1;

        if (full_range) {
            y = *buf++;
            cr = *buf++;
            cb = *buf++;
            alpha = *buf++;
        } else {
            y = buf[0] & 0xfc;
            cr = (((buf[0] & 3) << 2) | ((buf[1] >> 6) & 3)) << 4;
            cb = (buf[1] << 2) & 0xf0;
            alpha = (buf[1] << 6) & 0xc0;

            buf += 2;
        }

        if (y == 0)
            alpha = 0xff;

        YUV_TO_RGB1_CCIR(cb, cr);
        YUV_TO_RGB2_CCIR(r, g, b, y);

        ff_dlog(avctx, "clut %d := (%d,%d,%d,%d)\n", entry_id, r, g, b, alpha);
        if (!!(depth & 0x80) + !!(depth & 0x40) + !!(depth & 0x20) > 1) {
            ff_dlog(avctx, "More than one bit level marked: %x\n", depth);
            if (avctx->strict_std_compliance > FF_COMPLIANCE_NORMAL)
                return AVERROR_INVALIDDATA;
        }

        if (depth & 0x80 && entry_id < 4)
            clut->clut4[entry_id] = RGBA(r,g,b,255 - alpha);
        else if (depth & 0x40 && entry_id < 16)
            clut->clut16[entry_id] = RGBA(r,g,b,255 - alpha);
        else if (depth & 0x20)
            clut->clut256[entry_id] = RGBA(r,g,b,255 - alpha);
    }
    }

    return 0;
}