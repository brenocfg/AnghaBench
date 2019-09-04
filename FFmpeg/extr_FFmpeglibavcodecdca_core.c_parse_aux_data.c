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
struct TYPE_3__ {size_t prim_dmix_type; size_t audio_mode; int* prim_dmix_coeff; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; int /*<<< orphan*/  lfe_present; scalar_t__ prim_dmix_embedded; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 size_t DCA_DMIX_TYPE_COUNT ; 
 scalar_t__ DCA_SYNCWORD_REV1AUX ; 
 unsigned int FF_DCA_DMIXTABLE_SIZE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int* ff_dca_channels ; 
 scalar_t__ ff_dca_check_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int* ff_dca_dmix_primary_nch ; 
 int* ff_dca_dmixtable ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_aux_data(DCACoreDecoder *s)
{
    int aux_pos;

    if (get_bits_left(&s->gb) < 0)
        return AVERROR_INVALIDDATA;

    // Auxiliary data byte count (can't be trusted)
    skip_bits(&s->gb, 6);

    // 4-byte align
    skip_bits_long(&s->gb, -get_bits_count(&s->gb) & 31);

    // Auxiliary data sync word
    if (get_bits_long(&s->gb, 32) != DCA_SYNCWORD_REV1AUX) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid auxiliary data sync word\n");
        return AVERROR_INVALIDDATA;
    }

    aux_pos = get_bits_count(&s->gb);

    // Auxiliary decode time stamp flag
    if (get_bits1(&s->gb))
        skip_bits_long(&s->gb, 47);

    // Auxiliary dynamic downmix flag
    if (s->prim_dmix_embedded = get_bits1(&s->gb)) {
        int i, m, n;

        // Auxiliary primary channel downmix type
        s->prim_dmix_type = get_bits(&s->gb, 3);
        if (s->prim_dmix_type >= DCA_DMIX_TYPE_COUNT) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid primary channel set downmix type\n");
            return AVERROR_INVALIDDATA;
        }

        // Size of downmix coefficients matrix
        m = ff_dca_dmix_primary_nch[s->prim_dmix_type];
        n = ff_dca_channels[s->audio_mode] + !!s->lfe_present;

        // Dynamic downmix code coefficients
        for (i = 0; i < m * n; i++) {
            int code = get_bits(&s->gb, 9);
            int sign = (code >> 8) - 1;
            unsigned int index = code & 0xff;
            if (index >= FF_DCA_DMIXTABLE_SIZE) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid downmix coefficient index\n");
                return AVERROR_INVALIDDATA;
            }
            s->prim_dmix_coeff[i] = (ff_dca_dmixtable[index] ^ sign) - sign;
        }
    }

    // Byte align
    skip_bits(&s->gb, -get_bits_count(&s->gb) & 7);

    // CRC16 of auxiliary data
    skip_bits(&s->gb, 16);

    // Check CRC
    if (ff_dca_check_crc(s->avctx, &s->gb, aux_pos, get_bits_count(&s->gb))) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid auxiliary data checksum\n");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}