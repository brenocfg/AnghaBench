#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int npcmblocks; int es_format; int /*<<< orphan*/  sumdiff_surround; int /*<<< orphan*/  sumdiff_front; int /*<<< orphan*/  source_pcm_res; int /*<<< orphan*/  filter_perfect; int /*<<< orphan*/  predictor_history; int /*<<< orphan*/  lfe_present; int /*<<< orphan*/  sync_ssf; int /*<<< orphan*/  ext_audio_present; int /*<<< orphan*/  ext_audio_type; int /*<<< orphan*/  aux_present; int /*<<< orphan*/  ts_present; int /*<<< orphan*/  drc_present; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  audio_mode; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  crc_present; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
struct TYPE_5__ {int npcmblocks; size_t sr_code; size_t br_code; size_t pcmr_code; int /*<<< orphan*/  sumdiff_surround; int /*<<< orphan*/  sumdiff_front; int /*<<< orphan*/  filter_perfect; int /*<<< orphan*/  predictor_history; int /*<<< orphan*/  lfe_present; int /*<<< orphan*/  sync_ssf; int /*<<< orphan*/  ext_audio_present; int /*<<< orphan*/  ext_audio_type; int /*<<< orphan*/  aux_present; int /*<<< orphan*/  ts_present; int /*<<< orphan*/  drc_present; int /*<<< orphan*/  audio_mode; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  crc_present; int /*<<< orphan*/  normal_frame; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ DCACoreFrameHeader ;
typedef  TYPE_2__ DCACoreDecoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  DCA_PARSE_ERROR_AMODE 135 
#define  DCA_PARSE_ERROR_DEFICIT_SAMPLES 134 
#define  DCA_PARSE_ERROR_FRAME_SIZE 133 
#define  DCA_PARSE_ERROR_LFE_FLAG 132 
#define  DCA_PARSE_ERROR_PCM_BLOCKS 131 
#define  DCA_PARSE_ERROR_PCM_RES 130 
#define  DCA_PARSE_ERROR_RESERVED_BIT 129 
#define  DCA_PARSE_ERROR_SAMPLE_RATE 128 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * avpriv_dca_sample_rates ; 
 int /*<<< orphan*/ * ff_dca_bit_rates ; 
 int /*<<< orphan*/ * ff_dca_bits_per_sample ; 
 int ff_dca_parse_core_frame_header (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_frame_header(DCACoreDecoder *s)
{
    DCACoreFrameHeader h = { 0 };
    int err = ff_dca_parse_core_frame_header(&h, &s->gb);

    if (err < 0) {
        switch (err) {
        case DCA_PARSE_ERROR_DEFICIT_SAMPLES:
            av_log(s->avctx, AV_LOG_ERROR, "Deficit samples are not supported\n");
            return h.normal_frame ? AVERROR_INVALIDDATA : AVERROR_PATCHWELCOME;

        case DCA_PARSE_ERROR_PCM_BLOCKS:
            av_log(s->avctx, AV_LOG_ERROR, "Unsupported number of PCM sample blocks (%d)\n", h.npcmblocks);
            return (h.npcmblocks < 6 || h.normal_frame) ? AVERROR_INVALIDDATA : AVERROR_PATCHWELCOME;

        case DCA_PARSE_ERROR_FRAME_SIZE:
            av_log(s->avctx, AV_LOG_ERROR, "Invalid core frame size (%d bytes)\n", h.frame_size);
            return AVERROR_INVALIDDATA;

        case DCA_PARSE_ERROR_AMODE:
            av_log(s->avctx, AV_LOG_ERROR, "Unsupported audio channel arrangement (%d)\n", h.audio_mode);
            return AVERROR_PATCHWELCOME;

        case DCA_PARSE_ERROR_SAMPLE_RATE:
            av_log(s->avctx, AV_LOG_ERROR, "Invalid core audio sampling frequency\n");
            return AVERROR_INVALIDDATA;

        case DCA_PARSE_ERROR_RESERVED_BIT:
            av_log(s->avctx, AV_LOG_ERROR, "Reserved bit set\n");
            return AVERROR_INVALIDDATA;

        case DCA_PARSE_ERROR_LFE_FLAG:
            av_log(s->avctx, AV_LOG_ERROR, "Invalid low frequency effects flag\n");
            return AVERROR_INVALIDDATA;

        case DCA_PARSE_ERROR_PCM_RES:
            av_log(s->avctx, AV_LOG_ERROR, "Invalid source PCM resolution\n");
            return AVERROR_INVALIDDATA;

        default:
            av_log(s->avctx, AV_LOG_ERROR, "Unknown core frame header error\n");
            return AVERROR_INVALIDDATA;
        }
    }

    s->crc_present          = h.crc_present;
    s->npcmblocks           = h.npcmblocks;
    s->frame_size           = h.frame_size;
    s->audio_mode           = h.audio_mode;
    s->sample_rate          = avpriv_dca_sample_rates[h.sr_code];
    s->bit_rate             = ff_dca_bit_rates[h.br_code];
    s->drc_present          = h.drc_present;
    s->ts_present           = h.ts_present;
    s->aux_present          = h.aux_present;
    s->ext_audio_type       = h.ext_audio_type;
    s->ext_audio_present    = h.ext_audio_present;
    s->sync_ssf             = h.sync_ssf;
    s->lfe_present          = h.lfe_present;
    s->predictor_history    = h.predictor_history;
    s->filter_perfect       = h.filter_perfect;
    s->source_pcm_res       = ff_dca_bits_per_sample[h.pcmr_code];
    s->es_format            = h.pcmr_code & 1;
    s->sumdiff_front        = h.sumdiff_front;
    s->sumdiff_surround     = h.sumdiff_surround;

    return 0;
}