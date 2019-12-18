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
struct TYPE_3__ {size_t center_mix_level; size_t surround_mix_level; int fbw_channels; size_t channel_mode; scalar_t__ output_mode; void*** downmix_coeffs; } ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 int AC3_CHMODE_2F1R ; 
 int AC3_CHMODE_2F2R ; 
 int AC3_CHMODE_3F1R ; 
 int AC3_CHMODE_3F2R ; 
 scalar_t__ AC3_CHMODE_MONO ; 
 int AC3_MAX_CHANNELS ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FIXR12 (float) ; 
 float LEVEL_MINUS_3DB ; 
 size_t*** ac3_default_coeffs ; 
 void** av_malloc_array (int,int) ; 
 float* gain_levels ; 

__attribute__((used)) static int set_downmix_coeffs(AC3DecodeContext *s)
{
    int i;
    float cmix = gain_levels[s->  center_mix_level];
    float smix = gain_levels[s->surround_mix_level];
    float norm0, norm1;
    float downmix_coeffs[2][AC3_MAX_CHANNELS];

    if (!s->downmix_coeffs[0]) {
        s->downmix_coeffs[0] = av_malloc_array(2 * AC3_MAX_CHANNELS,
                                               sizeof(**s->downmix_coeffs));
        if (!s->downmix_coeffs[0])
            return AVERROR(ENOMEM);
        s->downmix_coeffs[1] = s->downmix_coeffs[0] + AC3_MAX_CHANNELS;
    }

    for (i = 0; i < s->fbw_channels; i++) {
        downmix_coeffs[0][i] = gain_levels[ac3_default_coeffs[s->channel_mode][i][0]];
        downmix_coeffs[1][i] = gain_levels[ac3_default_coeffs[s->channel_mode][i][1]];
    }
    if (s->channel_mode > 1 && s->channel_mode & 1) {
        downmix_coeffs[0][1] = downmix_coeffs[1][1] = cmix;
    }
    if (s->channel_mode == AC3_CHMODE_2F1R || s->channel_mode == AC3_CHMODE_3F1R) {
        int nf = s->channel_mode - 2;
        downmix_coeffs[0][nf] = downmix_coeffs[1][nf] = smix * LEVEL_MINUS_3DB;
    }
    if (s->channel_mode == AC3_CHMODE_2F2R || s->channel_mode == AC3_CHMODE_3F2R) {
        int nf = s->channel_mode - 4;
        downmix_coeffs[0][nf] = downmix_coeffs[1][nf+1] = smix;
    }

    /* renormalize */
    norm0 = norm1 = 0.0;
    for (i = 0; i < s->fbw_channels; i++) {
        norm0 += downmix_coeffs[0][i];
        norm1 += downmix_coeffs[1][i];
    }
    norm0 = 1.0f / norm0;
    norm1 = 1.0f / norm1;
    for (i = 0; i < s->fbw_channels; i++) {
        downmix_coeffs[0][i] *= norm0;
        downmix_coeffs[1][i] *= norm1;
    }

    if (s->output_mode == AC3_CHMODE_MONO) {
        for (i = 0; i < s->fbw_channels; i++)
            downmix_coeffs[0][i] = (downmix_coeffs[0][i] +
                                    downmix_coeffs[1][i]) * LEVEL_MINUS_3DB;
    }
    for (i = 0; i < s->fbw_channels; i++) {
        s->downmix_coeffs[0][i] = FIXR12(downmix_coeffs[0][i]);
        s->downmix_coeffs[1][i] = FIXR12(downmix_coeffs[1][i]);
    }

    return 0;
}