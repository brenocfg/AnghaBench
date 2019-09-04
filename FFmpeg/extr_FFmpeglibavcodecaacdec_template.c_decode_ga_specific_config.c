#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int warned_960_sbr; } ;
struct TYPE_7__ {int frame_length_short; int sbr; int ps; int object_type; } ;
typedef  TYPE_1__ MPEG4AudioConfig ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  TYPE_2__ AACContext ;

/* Variables and functions */
 int AOT_AAC_SCALABLE ; 
#define  AOT_ER_AAC_LC 132 
#define  AOT_ER_AAC_LD 131 
#define  AOT_ER_AAC_LTP 130 
#define  AOT_ER_AAC_SCALABLE 129 
#define  AOT_ER_BSAC 128 
 int AVERROR_PATCHWELCOME ; 
 int MAX_ELEM_ID ; 
 int /*<<< orphan*/  OC_GLOBAL_HDR ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ *,char*,...) ; 
 int count_channels (int /*<<< orphan*/ **,int) ; 
 int decode_pce (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int output_configure (TYPE_2__*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_default_channel_config (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_ga_specific_config(AACContext *ac, AVCodecContext *avctx,
                                     GetBitContext *gb,
                                     int get_bit_alignment,
                                     MPEG4AudioConfig *m4ac,
                                     int channel_config)
{
    int extension_flag, ret, ep_config, res_flags;
    uint8_t layout_map[MAX_ELEM_ID*4][3];
    int tags = 0;

#if USE_FIXED
    if (get_bits1(gb)) { // frameLengthFlag
        avpriv_report_missing_feature(avctx, "Fixed point 960/120 MDCT window");
        return AVERROR_PATCHWELCOME;
    }
    m4ac->frame_length_short = 0;
#else
    m4ac->frame_length_short = get_bits1(gb);
    if (m4ac->frame_length_short && m4ac->sbr == 1) {
      avpriv_report_missing_feature(avctx, "SBR with 960 frame length");
      if (ac) ac->warned_960_sbr = 1;
      m4ac->sbr = 0;
      m4ac->ps = 0;
    }
#endif

    if (get_bits1(gb))       // dependsOnCoreCoder
        skip_bits(gb, 14);   // coreCoderDelay
    extension_flag = get_bits1(gb);

    if (m4ac->object_type == AOT_AAC_SCALABLE ||
        m4ac->object_type == AOT_ER_AAC_SCALABLE)
        skip_bits(gb, 3);     // layerNr

    if (channel_config == 0) {
        skip_bits(gb, 4);  // element_instance_tag
        tags = decode_pce(avctx, m4ac, layout_map, gb, get_bit_alignment);
        if (tags < 0)
            return tags;
    } else {
        if ((ret = set_default_channel_config(avctx, layout_map,
                                              &tags, channel_config)))
            return ret;
    }

    if (count_channels(layout_map, tags) > 1) {
        m4ac->ps = 0;
    } else if (m4ac->sbr == 1 && m4ac->ps == -1)
        m4ac->ps = 1;

    if (ac && (ret = output_configure(ac, layout_map, tags, OC_GLOBAL_HDR, 0)))
        return ret;

    if (extension_flag) {
        switch (m4ac->object_type) {
        case AOT_ER_BSAC:
            skip_bits(gb, 5);    // numOfSubFrame
            skip_bits(gb, 11);   // layer_length
            break;
        case AOT_ER_AAC_LC:
        case AOT_ER_AAC_LTP:
        case AOT_ER_AAC_SCALABLE:
        case AOT_ER_AAC_LD:
            res_flags = get_bits(gb, 3);
            if (res_flags) {
                avpriv_report_missing_feature(avctx,
                                              "AAC data resilience (flags %x)",
                                              res_flags);
                return AVERROR_PATCHWELCOME;
            }
            break;
        }
        skip_bits1(gb);    // extensionFlag3 (TBD in version 3)
    }
    switch (m4ac->object_type) {
    case AOT_ER_AAC_LC:
    case AOT_ER_AAC_LTP:
    case AOT_ER_AAC_SCALABLE:
    case AOT_ER_AAC_LD:
        ep_config = get_bits(gb, 2);
        if (ep_config) {
            avpriv_report_missing_feature(avctx,
                                          "epConfig %d", ep_config);
            return AVERROR_PATCHWELCOME;
        }
    }
    return 0;
}