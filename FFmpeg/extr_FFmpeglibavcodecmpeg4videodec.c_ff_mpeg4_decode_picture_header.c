#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_29__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
struct TYPE_35__ {int size_in_bits; } ;
struct TYPE_32__ {int studio_profile; scalar_t__ codec_tag; int low_delay; TYPE_29__* avctx; } ;
struct TYPE_34__ {scalar_t__ divx_version; scalar_t__ xvid_build; TYPE_1__ m; } ;
struct TYPE_33__ {int bits_per_raw_sample; int debug; int profile; int level; int flags; int has_b_frames; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg4DecContext ;
typedef  TYPE_3__ GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int AV_CODEC_FLAG_LOW_DELAY ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_RL32 (char*) ; 
 int FF_DEBUG_STARTCODE ; 
 int FF_PROFILE_MPEG4_SIMPLE_STUDIO ; 
 int FRAME_SKIPPED ; 
 unsigned int GOP_STARTCODE ; 
 unsigned int USER_DATA_STARTCODE ; 
 unsigned int VISUAL_OBJ_STARTCODE ; 
 unsigned int VOP_STARTCODE ; 
 unsigned int VOS_STARTCODE ; 
 int /*<<< orphan*/  align_get_bits (TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (TYPE_29__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_29__*,char*) ; 
 int decode_studio_vop_header (TYPE_2__*,TYPE_3__*) ; 
 int decode_studiovisualobject (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  decode_user_data (TYPE_2__*,TYPE_3__*) ; 
 int decode_vol_header (TYPE_2__*,TYPE_3__*) ; 
 int decode_vop_header (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  extension_and_user_data (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int get_bits (TYPE_3__*,int) ; 
 int get_bits_count (TYPE_3__*) ; 
 int /*<<< orphan*/  mpeg4_decode_gop_header (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mpeg4_decode_profile_level (TYPE_1__*,TYPE_3__*,int*,int*) ; 
 int /*<<< orphan*/  mpeg4_decode_visual_object (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  next_start_code_studio (TYPE_3__*) ; 
 int show_bits (TYPE_3__*,int) ; 
 int /*<<< orphan*/  skip_bits (TYPE_3__*,int) ; 

int ff_mpeg4_decode_picture_header(Mpeg4DecContext *ctx, GetBitContext *gb, int header)
{
    MpegEncContext *s = &ctx->m;
    unsigned startcode, v;
    int ret;
    int vol = 0;

    /* search next start code */
    align_get_bits(gb);

    // If we have not switched to studio profile than we also did not switch bps
    // that means something else (like a previous instance) outside set bps which
    // would be inconsistant with the currect state, thus reset it
    if (!s->studio_profile && s->avctx->bits_per_raw_sample != 8)
        s->avctx->bits_per_raw_sample = 0;

    if (s->codec_tag == AV_RL32("WV1F") && show_bits(gb, 24) == 0x575630) {
        skip_bits(gb, 24);
        if (get_bits(gb, 8) == 0xF0)
            goto end;
    }

    startcode = 0xff;
    for (;;) {
        if (get_bits_count(gb) >= gb->size_in_bits) {
            if (gb->size_in_bits == 8 &&
                (ctx->divx_version >= 0 || ctx->xvid_build >= 0) || s->codec_tag == AV_RL32("QMP4")) {
                av_log(s->avctx, AV_LOG_VERBOSE, "frame skip %d\n", gb->size_in_bits);
                return FRAME_SKIPPED;  // divx bug
            } else if (header && get_bits_count(gb) == gb->size_in_bits) {
                return 0; // ordinary return value for parsing of extradata
            } else
                return AVERROR_INVALIDDATA;  // end of stream
        }

        /* use the bits after the test */
        v = get_bits(gb, 8);
        startcode = ((startcode << 8) | v) & 0xffffffff;

        if ((startcode & 0xFFFFFF00) != 0x100)
            continue;  // no startcode

        if (s->avctx->debug & FF_DEBUG_STARTCODE) {
            av_log(s->avctx, AV_LOG_DEBUG, "startcode: %3X ", startcode);
            if (startcode <= 0x11F)
                av_log(s->avctx, AV_LOG_DEBUG, "Video Object Start");
            else if (startcode <= 0x12F)
                av_log(s->avctx, AV_LOG_DEBUG, "Video Object Layer Start");
            else if (startcode <= 0x13F)
                av_log(s->avctx, AV_LOG_DEBUG, "Reserved");
            else if (startcode <= 0x15F)
                av_log(s->avctx, AV_LOG_DEBUG, "FGS bp start");
            else if (startcode <= 0x1AF)
                av_log(s->avctx, AV_LOG_DEBUG, "Reserved");
            else if (startcode == 0x1B0)
                av_log(s->avctx, AV_LOG_DEBUG, "Visual Object Seq Start");
            else if (startcode == 0x1B1)
                av_log(s->avctx, AV_LOG_DEBUG, "Visual Object Seq End");
            else if (startcode == 0x1B2)
                av_log(s->avctx, AV_LOG_DEBUG, "User Data");
            else if (startcode == 0x1B3)
                av_log(s->avctx, AV_LOG_DEBUG, "Group of VOP start");
            else if (startcode == 0x1B4)
                av_log(s->avctx, AV_LOG_DEBUG, "Video Session Error");
            else if (startcode == 0x1B5)
                av_log(s->avctx, AV_LOG_DEBUG, "Visual Object Start");
            else if (startcode == 0x1B6)
                av_log(s->avctx, AV_LOG_DEBUG, "Video Object Plane start");
            else if (startcode == 0x1B7)
                av_log(s->avctx, AV_LOG_DEBUG, "slice start");
            else if (startcode == 0x1B8)
                av_log(s->avctx, AV_LOG_DEBUG, "extension start");
            else if (startcode == 0x1B9)
                av_log(s->avctx, AV_LOG_DEBUG, "fgs start");
            else if (startcode == 0x1BA)
                av_log(s->avctx, AV_LOG_DEBUG, "FBA Object start");
            else if (startcode == 0x1BB)
                av_log(s->avctx, AV_LOG_DEBUG, "FBA Object Plane start");
            else if (startcode == 0x1BC)
                av_log(s->avctx, AV_LOG_DEBUG, "Mesh Object start");
            else if (startcode == 0x1BD)
                av_log(s->avctx, AV_LOG_DEBUG, "Mesh Object Plane start");
            else if (startcode == 0x1BE)
                av_log(s->avctx, AV_LOG_DEBUG, "Still Texture Object start");
            else if (startcode == 0x1BF)
                av_log(s->avctx, AV_LOG_DEBUG, "Texture Spatial Layer start");
            else if (startcode == 0x1C0)
                av_log(s->avctx, AV_LOG_DEBUG, "Texture SNR Layer start");
            else if (startcode == 0x1C1)
                av_log(s->avctx, AV_LOG_DEBUG, "Texture Tile start");
            else if (startcode == 0x1C2)
                av_log(s->avctx, AV_LOG_DEBUG, "Texture Shape Layer start");
            else if (startcode == 0x1C3)
                av_log(s->avctx, AV_LOG_DEBUG, "stuffing start");
            else if (startcode <= 0x1C5)
                av_log(s->avctx, AV_LOG_DEBUG, "reserved");
            else if (startcode <= 0x1FF)
                av_log(s->avctx, AV_LOG_DEBUG, "System start");
            av_log(s->avctx, AV_LOG_DEBUG, " at %d\n", get_bits_count(gb));
        }

        if (startcode >= 0x120 && startcode <= 0x12F) {
            if (vol) {
                av_log(s->avctx, AV_LOG_WARNING, "Ignoring multiple VOL headers\n");
                continue;
            }
            vol++;
            if ((ret = decode_vol_header(ctx, gb)) < 0)
                return ret;
        } else if (startcode == USER_DATA_STARTCODE) {
            decode_user_data(ctx, gb);
        } else if (startcode == GOP_STARTCODE) {
            mpeg4_decode_gop_header(s, gb);
        } else if (startcode == VOS_STARTCODE) {
            int profile, level;
            mpeg4_decode_profile_level(s, gb, &profile, &level);
            if (profile == FF_PROFILE_MPEG4_SIMPLE_STUDIO &&
                (level > 0 && level < 9)) {
                s->studio_profile = 1;
                next_start_code_studio(gb);
                extension_and_user_data(s, gb, 0);
            } else if (s->studio_profile) {
                avpriv_request_sample(s->avctx, "Mixes studio and non studio profile\n");
                return AVERROR_PATCHWELCOME;
            }
            s->avctx->profile = profile;
            s->avctx->level   = level;
        } else if (startcode == VISUAL_OBJ_STARTCODE) {
            if (s->studio_profile) {
                if ((ret = decode_studiovisualobject(ctx, gb)) < 0)
                    return ret;
            } else
                mpeg4_decode_visual_object(s, gb);
        } else if (startcode == VOP_STARTCODE) {
            break;
        }

        align_get_bits(gb);
        startcode = 0xff;
    }

end:
    if (s->avctx->flags & AV_CODEC_FLAG_LOW_DELAY)
        s->low_delay = 1;
    s->avctx->has_b_frames = !s->low_delay;

    if (s->studio_profile) {
        if (!s->avctx->bits_per_raw_sample) {
            av_log(s->avctx, AV_LOG_ERROR, "Missing VOL header\n");
            return AVERROR_INVALIDDATA;
        }
        return decode_studio_vop_header(ctx, gb);
    } else
        return decode_vop_header(ctx, gb);
}