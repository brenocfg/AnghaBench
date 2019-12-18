#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ frame_length_short; scalar_t__ sbr; scalar_t__ ps; } ;
typedef  TYPE_1__ MPEG4AudioConfig ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AACContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int MAX_ELEM_ID ; 
 int /*<<< orphan*/  OC_GLOBAL_HDR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ *,char*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int output_configure (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  overread_err ; 
 int set_default_channel_config (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_eld_specific_config(AACContext *ac, AVCodecContext *avctx,
                                     GetBitContext *gb,
                                     MPEG4AudioConfig *m4ac,
                                     int channel_config)
{
    int ret, ep_config, res_flags;
    uint8_t layout_map[MAX_ELEM_ID*4][3];
    int tags = 0;
    const int ELDEXT_TERM = 0;

    m4ac->ps  = 0;
    m4ac->sbr = 0;
#if USE_FIXED
    if (get_bits1(gb)) { // frameLengthFlag
        avpriv_request_sample(avctx, "960/120 MDCT window");
        return AVERROR_PATCHWELCOME;
    }
#else
    m4ac->frame_length_short = get_bits1(gb);
#endif
    res_flags = get_bits(gb, 3);
    if (res_flags) {
        avpriv_report_missing_feature(avctx,
                                      "AAC data resilience (flags %x)",
                                      res_flags);
        return AVERROR_PATCHWELCOME;
    }

    if (get_bits1(gb)) { // ldSbrPresentFlag
        avpriv_report_missing_feature(avctx,
                                      "Low Delay SBR");
        return AVERROR_PATCHWELCOME;
    }

    while (get_bits(gb, 4) != ELDEXT_TERM) {
        int len = get_bits(gb, 4);
        if (len == 15)
            len += get_bits(gb, 8);
        if (len == 15 + 255)
            len += get_bits(gb, 16);
        if (get_bits_left(gb) < len * 8 + 4) {
            av_log(avctx, AV_LOG_ERROR, overread_err);
            return AVERROR_INVALIDDATA;
        }
        skip_bits_long(gb, 8 * len);
    }

    if ((ret = set_default_channel_config(avctx, layout_map,
                                          &tags, channel_config)))
        return ret;

    if (ac && (ret = output_configure(ac, layout_map, tags, OC_GLOBAL_HDR, 0)))
        return ret;

    ep_config = get_bits(gb, 2);
    if (ep_config) {
        avpriv_report_missing_feature(avctx,
                                      "epConfig %d", ep_config);
        return AVERROR_PATCHWELCOME;
    }
    return 0;
}