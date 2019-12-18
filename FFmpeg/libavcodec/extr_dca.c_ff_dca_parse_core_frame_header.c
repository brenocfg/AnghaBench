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
struct TYPE_3__ {scalar_t__ deficit_samples; int npcmblocks; int frame_size; scalar_t__ audio_mode; size_t sr_code; scalar_t__ lfe_present; size_t pcmr_code; void* dn_code; void* sumdiff_surround; void* sumdiff_front; void* copy_hist; void* encoder_rev; void* filter_perfect; void* crc_present; void* predictor_history; void* sync_ssf; void* ext_audio_present; void* ext_audio_type; void* hdcd_master; void* aux_present; void* ts_present; void* drc_present; void* br_code; void* normal_frame; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ DCACoreFrameHeader ;

/* Variables and functions */
 scalar_t__ DCA_AMODE_COUNT ; 
 scalar_t__ DCA_LFE_FLAG_INVALID ; 
 int DCA_PARSE_ERROR_AMODE ; 
 int DCA_PARSE_ERROR_DEFICIT_SAMPLES ; 
 int DCA_PARSE_ERROR_FRAME_SIZE ; 
 int DCA_PARSE_ERROR_LFE_FLAG ; 
 int DCA_PARSE_ERROR_PCM_BLOCKS ; 
 int DCA_PARSE_ERROR_PCM_RES ; 
 int DCA_PARSE_ERROR_RESERVED_BIT ; 
 int DCA_PARSE_ERROR_SAMPLE_RATE ; 
 int DCA_PARSE_ERROR_SYNC_WORD ; 
 scalar_t__ DCA_PCMBLOCK_SAMPLES ; 
 int DCA_SUBBAND_SAMPLES ; 
 scalar_t__ DCA_SYNCWORD_CORE_BE ; 
 int /*<<< orphan*/ * avpriv_dca_sample_rates ; 
 int /*<<< orphan*/ * ff_dca_bits_per_sample ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

int ff_dca_parse_core_frame_header(DCACoreFrameHeader *h, GetBitContext *gb)
{
    if (get_bits_long(gb, 32) != DCA_SYNCWORD_CORE_BE)
        return DCA_PARSE_ERROR_SYNC_WORD;

    h->normal_frame = get_bits1(gb);
    h->deficit_samples = get_bits(gb, 5) + 1;
    if (h->deficit_samples != DCA_PCMBLOCK_SAMPLES)
        return DCA_PARSE_ERROR_DEFICIT_SAMPLES;

    h->crc_present = get_bits1(gb);
    h->npcmblocks = get_bits(gb, 7) + 1;
    if (h->npcmblocks & (DCA_SUBBAND_SAMPLES - 1))
        return DCA_PARSE_ERROR_PCM_BLOCKS;

    h->frame_size = get_bits(gb, 14) + 1;
    if (h->frame_size < 96)
        return DCA_PARSE_ERROR_FRAME_SIZE;

    h->audio_mode = get_bits(gb, 6);
    if (h->audio_mode >= DCA_AMODE_COUNT)
        return DCA_PARSE_ERROR_AMODE;

    h->sr_code = get_bits(gb, 4);
    if (!avpriv_dca_sample_rates[h->sr_code])
        return DCA_PARSE_ERROR_SAMPLE_RATE;

    h->br_code = get_bits(gb, 5);
    if (get_bits1(gb))
        return DCA_PARSE_ERROR_RESERVED_BIT;

    h->drc_present = get_bits1(gb);
    h->ts_present = get_bits1(gb);
    h->aux_present = get_bits1(gb);
    h->hdcd_master = get_bits1(gb);
    h->ext_audio_type = get_bits(gb, 3);
    h->ext_audio_present = get_bits1(gb);
    h->sync_ssf = get_bits1(gb);
    h->lfe_present = get_bits(gb, 2);
    if (h->lfe_present == DCA_LFE_FLAG_INVALID)
        return DCA_PARSE_ERROR_LFE_FLAG;

    h->predictor_history = get_bits1(gb);
    if (h->crc_present)
        skip_bits(gb, 16);
    h->filter_perfect = get_bits1(gb);
    h->encoder_rev = get_bits(gb, 4);
    h->copy_hist = get_bits(gb, 2);
    h->pcmr_code = get_bits(gb, 3);
    if (!ff_dca_bits_per_sample[h->pcmr_code])
        return DCA_PARSE_ERROR_PCM_RES;

    h->sumdiff_front = get_bits1(gb);
    h->sumdiff_surround = get_bits1(gb);
    h->dn_code = get_bits(gb, 4);
    return 0;
}