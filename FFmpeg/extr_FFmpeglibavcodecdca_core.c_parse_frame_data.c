#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum HeaderType { ____Placeholder_HeaderType } HeaderType ;
struct TYPE_6__ {int nsubframes; int nchannels; int* nsubbands; int* joint_intensity_index; int** subband_samples; int npcmblocks; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  AV_COPY128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DCA_ADPCM_COEFFS ; 
 int DCA_LFE_HISTORY ; 
 int DCA_SUBBANDS ; 
 int FFMAX (int,int) ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int parse_coding_header (TYPE_1__*,int,int) ; 
 int parse_subframe_audio (TYPE_1__*,int,int,int,int*,int*) ; 
 int parse_subframe_header (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static int parse_frame_data(DCACoreDecoder *s, enum HeaderType header, int xch_base)
{
    int sf, ch, ret, band, sub_pos, lfe_pos;

    if ((ret = parse_coding_header(s, header, xch_base)) < 0)
        return ret;

    for (sf = 0, sub_pos = 0, lfe_pos = DCA_LFE_HISTORY; sf < s->nsubframes; sf++) {
        if ((ret = parse_subframe_header(s, sf, header, xch_base)) < 0)
            return ret;
        if ((ret = parse_subframe_audio(s, sf, header, xch_base, &sub_pos, &lfe_pos)) < 0)
            return ret;
    }

    for (ch = xch_base; ch < s->nchannels; ch++) {
        // Determine number of active subbands for this channel
        int nsubbands = s->nsubbands[ch];
        if (s->joint_intensity_index[ch])
            nsubbands = FFMAX(nsubbands, s->nsubbands[s->joint_intensity_index[ch] - 1]);

        // Update history for ADPCM
        for (band = 0; band < nsubbands; band++) {
            int32_t *samples = s->subband_samples[ch][band] - DCA_ADPCM_COEFFS;
            AV_COPY128(samples, samples + s->npcmblocks);
        }

        // Clear inactive subbands
        for (; band < DCA_SUBBANDS; band++) {
            int32_t *samples = s->subband_samples[ch][band] - DCA_ADPCM_COEFFS;
            memset(samples, 0, (DCA_ADPCM_COEFFS + s->npcmblocks) * sizeof(int32_t));
        }
    }

    emms_c();

    return 0;
}