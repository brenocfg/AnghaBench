#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  avctx; } ;
struct LATMContext {int audio_mux_version_A; int frame_length_type; int frame_length; TYPE_1__ aac_ctx; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int latm_decode_audio_specific_config (struct LATMContext*,int /*<<< orphan*/ *,int) ; 
 int latm_get_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_stream_mux_config(struct LATMContext *latmctx,
                                  GetBitContext *gb)
{
    int ret, audio_mux_version = get_bits(gb, 1);

    latmctx->audio_mux_version_A = 0;
    if (audio_mux_version)
        latmctx->audio_mux_version_A = get_bits(gb, 1);

    if (!latmctx->audio_mux_version_A) {

        if (audio_mux_version)
            latm_get_value(gb);                 // taraFullness

        skip_bits(gb, 1);                       // allStreamSameTimeFraming
        skip_bits(gb, 6);                       // numSubFrames
        // numPrograms
        if (get_bits(gb, 4)) {                  // numPrograms
            avpriv_request_sample(latmctx->aac_ctx.avctx, "Multiple programs");
            return AVERROR_PATCHWELCOME;
        }

        // for each program (which there is only one in DVB)

        // for each layer (which there is only one in DVB)
        if (get_bits(gb, 3)) {                   // numLayer
            avpriv_request_sample(latmctx->aac_ctx.avctx, "Multiple layers");
            return AVERROR_PATCHWELCOME;
        }

        // for all but first stream: use_same_config = get_bits(gb, 1);
        if (!audio_mux_version) {
            if ((ret = latm_decode_audio_specific_config(latmctx, gb, 0)) < 0)
                return ret;
        } else {
            int ascLen = latm_get_value(gb);
            if ((ret = latm_decode_audio_specific_config(latmctx, gb, ascLen)) < 0)
                return ret;
        }

        latmctx->frame_length_type = get_bits(gb, 3);
        switch (latmctx->frame_length_type) {
        case 0:
            skip_bits(gb, 8);       // latmBufferFullness
            break;
        case 1:
            latmctx->frame_length = get_bits(gb, 9);
            break;
        case 3:
        case 4:
        case 5:
            skip_bits(gb, 6);       // CELP frame length table index
            break;
        case 6:
        case 7:
            skip_bits(gb, 1);       // HVXC frame length table index
            break;
        }

        if (get_bits(gb, 1)) {                  // other data
            if (audio_mux_version) {
                latm_get_value(gb);             // other_data_bits
            } else {
                int esc;
                do {
                    if (get_bits_left(gb) < 9)
                        return AVERROR_INVALIDDATA;
                    esc = get_bits(gb, 1);
                    skip_bits(gb, 8);
                } while (esc);
            }
        }

        if (get_bits(gb, 1))                     // crc present
            skip_bits(gb, 8);                    // config_crc
    }

    return 0;
}