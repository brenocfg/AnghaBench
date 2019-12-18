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
typedef  int uint8_t ;
typedef  enum dv_pack_type { ____Placeholder_dv_pack_type } dv_pack_type ;
struct TYPE_9__ {scalar_t__ pix_fmt; int dsf; int video_stype; } ;
struct TYPE_8__ {TYPE_5__* sys; TYPE_2__* avctx; TYPE_1__* frame; } ;
struct TYPE_7__ {int height; int width; int /*<<< orphan*/  sample_aspect_ratio; } ;
struct TYPE_6__ {scalar_t__ top_field_first; } ;
typedef  TYPE_3__ DVVideoContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 scalar_t__ DV_PROFILE_IS_HD (TYPE_5__*) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
#define  dv_header525 131 
#define  dv_header625 130 
#define  dv_video_control 129 
#define  dv_video_source 128 

__attribute__((used)) static inline int dv_write_pack(enum dv_pack_type pack_id, DVVideoContext *c,
                                uint8_t *buf)
{
    /*
     * Here's what SMPTE314M says about these two:
     *    (page 6) APTn, AP1n, AP2n, AP3n: These data shall be identical
     *             as track application IDs (APTn = 001, AP1n =
     *             001, AP2n = 001, AP3n = 001), if the source signal
     *             comes from a digital VCR. If the signal source is
     *             unknown, all bits for these data shall be set to 1.
     *    (page 12) STYPE: STYPE defines a signal type of video signal
     *                     00000b = 4:1:1 compression
     *                     00100b = 4:2:2 compression
     *                     XXXXXX = Reserved
     * Now, I've got two problems with these statements:
     *   1. it looks like APT == 111b should be a safe bet, but it isn't.
     *      It seems that for PAL as defined in IEC 61834 we have to set
     *      APT to 000 and for SMPTE314M to 001.
     *   2. It is not at all clear what STYPE is used for 4:2:0 PAL
     *      compression scheme (if any).
     */
    uint8_t aspect = 0;
    int apt = (c->sys->pix_fmt == AV_PIX_FMT_YUV420P ? 0 : 1);
    int fs;

    if (c->avctx->height >= 720)
        fs = c->avctx->height == 720 || c->frame->top_field_first ? 0x40 : 0x00;
    else
        fs = c->frame->top_field_first ? 0x00 : 0x40;

    if (DV_PROFILE_IS_HD(c->sys) ||
        (int)(av_q2d(c->avctx->sample_aspect_ratio) *
              c->avctx->width / c->avctx->height * 10) >= 17)
        /* HD formats are always 16:9 */
        aspect = 0x02;

    buf[0] = (uint8_t) pack_id;
    switch (pack_id) {
    case dv_header525: /* I can't imagine why these two weren't defined as real */
    case dv_header625: /* packs in SMPTE314M -- they definitely look like ones */
        buf[1] =  0xf8       | /* reserved -- always 1 */
                 (apt & 0x07); /* APT: Track application ID */
        buf[2] = (0    << 7) | /* TF1: audio data is 0 - valid; 1 - invalid */
                 (0x0f << 3) | /* reserved -- always 1 */
                 (apt & 0x07); /* AP1: Audio application ID */
        buf[3] = (0    << 7) | /* TF2: video data is 0 - valid; 1 - invalid */
                 (0x0f << 3) | /* reserved -- always 1 */
                 (apt & 0x07); /* AP2: Video application ID */
        buf[4] = (0    << 7) | /* TF3: subcode(SSYB) is 0 - valid; 1 - invalid */
                 (0x0f << 3) | /* reserved -- always 1 */
                 (apt & 0x07); /* AP3: Subcode application ID */
        break;
    case dv_video_source:
        buf[1] = 0xff;         /* reserved -- always 1 */
        buf[2] = (1 << 7) |    /* B/W: 0 - b/w, 1 - color */
                 (1 << 6) |    /* following CLF is valid - 0, invalid - 1 */
                 (3 << 4) |    /* CLF: color frames ID (see ITU-R BT.470-4) */
                 0xf;          /* reserved -- always 1 */
        buf[3] = (3 << 6)           | /* reserved -- always 1 */
                 (c->sys->dsf << 5) | /*  system: 60fields/50fields */
                 c->sys->video_stype; /* signal type video compression */
        buf[4] = 0xff;         /* VISC: 0xff -- no information */
        break;
    case dv_video_control:
        buf[1] = (0 << 6) |    /* Copy generation management (CGMS) 0 -- free */
                 0x3f;         /* reserved -- always 1 */
        buf[2] = 0xc8 |        /* reserved -- always b11001xxx */
                 aspect;
        buf[3] = (1 << 7) |    /* frame/field flag 1 -- frame, 0 -- field */
                 fs       |    /* first/second field flag 0 -- field 2, 1 -- field 1 */
                 (1 << 5) |    /* frame change flag 0 -- same picture as before, 1 -- different */
                 (1 << 4) |    /* 1 - interlaced, 0 - noninterlaced */
                 0xc;          /* reserved -- always b1100 */
        buf[4] = 0xff;         /* reserved -- always 1 */
        break;
    default:
        buf[1] =
        buf[2] =
        buf[3] =
        buf[4] = 0xff;
    }
    return 5;
}