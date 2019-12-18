#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int strict_std_compliance; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_CHANNEL_SIDE ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int FF_COMPLIANCE_STRICT ; 
 int /*<<< orphan*/ * aac_channel_layout_map ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int* tags_per_config ; 

__attribute__((used)) static int set_default_channel_config(AVCodecContext *avctx,
                                      uint8_t (*layout_map)[3],
                                      int *tags,
                                      int channel_config)
{
    if (channel_config < 1 || (channel_config > 7 && channel_config < 11) ||
        channel_config > 12) {
        av_log(avctx, AV_LOG_ERROR,
               "invalid default channel configuration (%d)\n",
               channel_config);
        return AVERROR_INVALIDDATA;
    }
    *tags = tags_per_config[channel_config];
    memcpy(layout_map, aac_channel_layout_map[channel_config - 1],
           *tags * sizeof(*layout_map));

    /*
     * AAC specification has 7.1(wide) as a default layout for 8-channel streams.
     * However, at least Nero AAC encoder encodes 7.1 streams using the default
     * channel config 7, mapping the side channels of the original audio stream
     * to the second AAC_CHANNEL_FRONT pair in the AAC stream. Similarly, e.g. FAAD
     * decodes the second AAC_CHANNEL_FRONT pair as side channels, therefore decoding
     * the incorrect streams as if they were correct (and as the encoder intended).
     *
     * As actual intended 7.1(wide) streams are very rare, default to assuming a
     * 7.1 layout was intended.
     */
    if (channel_config == 7 && avctx->strict_std_compliance < FF_COMPLIANCE_STRICT) {
        av_log(avctx, AV_LOG_INFO, "Assuming an incorrectly encoded 7.1 channel layout"
               " instead of a spec-compliant 7.1(wide) layout, use -strict %d to decode"
               " according to the specification instead.\n", FF_COMPLIANCE_STRICT);
        layout_map[2][2] = AAC_CHANNEL_SIDE;
    }

    return 0;
}