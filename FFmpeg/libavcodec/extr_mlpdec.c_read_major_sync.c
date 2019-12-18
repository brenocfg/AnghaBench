#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ codec_id; scalar_t__ sample_rate; scalar_t__ frame_size; int bits_per_raw_sample; scalar_t__ sample_fmt; int channels; void* channel_layout; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* mlp_select_pack_output ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  mlp_pack_output; } ;
struct TYPE_13__ {scalar_t__ access_unit_size; scalar_t__ access_unit_size_pow2; int num_substreams; size_t max_decoded_substream; int params_valid; int needs_reordering; TYPE_2__* substream; TYPE_6__* avctx; TYPE_1__ dsp; int /*<<< orphan*/  major_sync_header_size; } ;
struct TYPE_12__ {int group1_bits; int group2_bits; scalar_t__ group2_samplerate; scalar_t__ group1_samplerate; scalar_t__ access_unit_size; scalar_t__ access_unit_size_pow2; int num_substreams; int stream_type; int channel_layout_mlp; int channel_layout_thd_stream2; int channel_layout_thd_stream1; int channel_arrangement; scalar_t__ channel_modifier_thd_stream2; scalar_t__ channel_modifier_thd_stream1; int channel_modifier_thd_stream0; int /*<<< orphan*/  header_size; } ;
struct TYPE_11__ {int mask; void* matrix_encoding; scalar_t__ restart_seen; int /*<<< orphan*/  max_matrix_channel; int /*<<< orphan*/  output_shift; int /*<<< orphan*/  ch_assign; } ;
typedef  TYPE_3__ MLPHeaderInfo ;
typedef  TYPE_4__ MLPDecodeContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ AV_CH_LAYOUT_MONO ; 
 void* AV_CH_LAYOUT_STEREO ; 
 int AV_CH_SIDE_LEFT ; 
 int AV_CH_SIDE_RIGHT ; 
 scalar_t__ AV_CODEC_ID_MLP ; 
 scalar_t__ AV_CODEC_ID_TRUEHD ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 void* AV_MATRIX_ENCODING_DOLBY ; 
 void* AV_MATRIX_ENCODING_DOLBYEX ; 
 void* AV_MATRIX_ENCODING_DOLBYHEADPHONE ; 
 void* AV_MATRIX_ENCODING_NONE ; 
 scalar_t__ AV_SAMPLE_FMT_S16 ; 
 scalar_t__ AV_SAMPLE_FMT_S32 ; 
 size_t FFMIN (int,int) ; 
 scalar_t__ MAX_BLOCKSIZE ; 
 scalar_t__ MAX_BLOCKSIZE_POW2 ; 
 scalar_t__ MAX_SAMPLERATE ; 
 int MAX_SUBSTREAMS ; 
#define  THD_CH_MODIFIER_LBINRBIN 129 
#define  THD_CH_MODIFIER_LTRT 128 
 scalar_t__ THD_CH_MODIFIER_SURROUNDEX ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_6__*,char*,int) ; 
 int ff_mlp_read_major_sync (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_major_sync(MLPDecodeContext *m, GetBitContext *gb)
{
    MLPHeaderInfo mh;
    int substr, ret;

    if ((ret = ff_mlp_read_major_sync(m->avctx, &mh, gb)) != 0)
        return ret;

    if (mh.group1_bits == 0) {
        av_log(m->avctx, AV_LOG_ERROR, "invalid/unknown bits per sample\n");
        return AVERROR_INVALIDDATA;
    }
    if (mh.group2_bits > mh.group1_bits) {
        av_log(m->avctx, AV_LOG_ERROR,
               "Channel group 2 cannot have more bits per sample than group 1.\n");
        return AVERROR_INVALIDDATA;
    }

    if (mh.group2_samplerate && mh.group2_samplerate != mh.group1_samplerate) {
        av_log(m->avctx, AV_LOG_ERROR,
               "Channel groups with differing sample rates are not currently supported.\n");
        return AVERROR_INVALIDDATA;
    }

    if (mh.group1_samplerate == 0) {
        av_log(m->avctx, AV_LOG_ERROR, "invalid/unknown sampling rate\n");
        return AVERROR_INVALIDDATA;
    }
    if (mh.group1_samplerate > MAX_SAMPLERATE) {
        av_log(m->avctx, AV_LOG_ERROR,
               "Sampling rate %d is greater than the supported maximum (%d).\n",
               mh.group1_samplerate, MAX_SAMPLERATE);
        return AVERROR_INVALIDDATA;
    }
    if (mh.access_unit_size > MAX_BLOCKSIZE) {
        av_log(m->avctx, AV_LOG_ERROR,
               "Block size %d is greater than the supported maximum (%d).\n",
               mh.access_unit_size, MAX_BLOCKSIZE);
        return AVERROR_INVALIDDATA;
    }
    if (mh.access_unit_size_pow2 > MAX_BLOCKSIZE_POW2) {
        av_log(m->avctx, AV_LOG_ERROR,
               "Block size pow2 %d is greater than the supported maximum (%d).\n",
               mh.access_unit_size_pow2, MAX_BLOCKSIZE_POW2);
        return AVERROR_INVALIDDATA;
    }

    if (mh.num_substreams == 0)
        return AVERROR_INVALIDDATA;
    if (m->avctx->codec_id == AV_CODEC_ID_MLP && mh.num_substreams > 2) {
        av_log(m->avctx, AV_LOG_ERROR, "MLP only supports up to 2 substreams.\n");
        return AVERROR_INVALIDDATA;
    }
    if (mh.num_substreams > MAX_SUBSTREAMS) {
        avpriv_request_sample(m->avctx,
                              "%d substreams (more than the "
                              "maximum supported by the decoder)",
                              mh.num_substreams);
        return AVERROR_PATCHWELCOME;
    }

    m->major_sync_header_size = mh.header_size;

    m->access_unit_size      = mh.access_unit_size;
    m->access_unit_size_pow2 = mh.access_unit_size_pow2;

    m->num_substreams        = mh.num_substreams;

    /* limit to decoding 3 substreams, as the 4th is used by Dolby Atmos for non-audio data */
    m->max_decoded_substream = FFMIN(m->num_substreams - 1, 2);

    m->avctx->sample_rate    = mh.group1_samplerate;
    m->avctx->frame_size     = mh.access_unit_size;

    m->avctx->bits_per_raw_sample = mh.group1_bits;
    if (mh.group1_bits > 16)
        m->avctx->sample_fmt = AV_SAMPLE_FMT_S32;
    else
        m->avctx->sample_fmt = AV_SAMPLE_FMT_S16;
    m->dsp.mlp_pack_output = m->dsp.mlp_select_pack_output(m->substream[m->max_decoded_substream].ch_assign,
                                                           m->substream[m->max_decoded_substream].output_shift,
                                                           m->substream[m->max_decoded_substream].max_matrix_channel,
                                                           m->avctx->sample_fmt == AV_SAMPLE_FMT_S32);

    m->params_valid = 1;
    for (substr = 0; substr < MAX_SUBSTREAMS; substr++)
        m->substream[substr].restart_seen = 0;

    /* Set the layout for each substream. When there's more than one, the first
     * substream is Stereo. Subsequent substreams' layouts are indicated in the
     * major sync. */
    if (m->avctx->codec_id == AV_CODEC_ID_MLP) {
        if (mh.stream_type != 0xbb) {
            avpriv_request_sample(m->avctx,
                        "unexpected stream_type %X in MLP",
                        mh.stream_type);
            return AVERROR_PATCHWELCOME;
        }
        if ((substr = (mh.num_substreams > 1)))
            m->substream[0].mask = AV_CH_LAYOUT_STEREO;
        m->substream[substr].mask = mh.channel_layout_mlp;
    } else {
        if (mh.stream_type != 0xba) {
            avpriv_request_sample(m->avctx,
                        "unexpected stream_type %X in !MLP",
                        mh.stream_type);
            return AVERROR_PATCHWELCOME;
        }
        if ((substr = (mh.num_substreams > 1)))
            m->substream[0].mask = AV_CH_LAYOUT_STEREO;
        if (mh.num_substreams > 2)
            if (mh.channel_layout_thd_stream2)
                m->substream[2].mask = mh.channel_layout_thd_stream2;
            else
                m->substream[2].mask = mh.channel_layout_thd_stream1;
        m->substream[substr].mask = mh.channel_layout_thd_stream1;

        if (m->avctx->channels<=2 && m->substream[substr].mask == AV_CH_LAYOUT_MONO && m->max_decoded_substream == 1) {
            av_log(m->avctx, AV_LOG_DEBUG, "Mono stream with 2 substreams, ignoring 2nd\n");
            m->max_decoded_substream = 0;
            if (m->avctx->channels==2)
                m->avctx->channel_layout = AV_CH_LAYOUT_STEREO;
        }
    }

    m->needs_reordering = mh.channel_arrangement >= 18 && mh.channel_arrangement <= 20;

    /* Parse the TrueHD decoder channel modifiers and set each substream's
     * AVMatrixEncoding accordingly.
     *
     * The meaning of the modifiers depends on the channel layout:
     *
     * - THD_CH_MODIFIER_LTRT, THD_CH_MODIFIER_LBINRBIN only apply to 2-channel
     *
     * - THD_CH_MODIFIER_MONO applies to 1-channel or 2-channel (dual mono)
     *
     * - THD_CH_MODIFIER_SURROUNDEX, THD_CH_MODIFIER_NOTSURROUNDEX only apply to
     *   layouts with an Ls/Rs channel pair
     */
    for (substr = 0; substr < MAX_SUBSTREAMS; substr++)
        m->substream[substr].matrix_encoding = AV_MATRIX_ENCODING_NONE;
    if (m->avctx->codec_id == AV_CODEC_ID_TRUEHD) {
        if (mh.num_substreams > 2 &&
            mh.channel_layout_thd_stream2 & AV_CH_SIDE_LEFT &&
            mh.channel_layout_thd_stream2 & AV_CH_SIDE_RIGHT &&
            mh.channel_modifier_thd_stream2 == THD_CH_MODIFIER_SURROUNDEX)
            m->substream[2].matrix_encoding = AV_MATRIX_ENCODING_DOLBYEX;

        if (mh.num_substreams > 1 &&
            mh.channel_layout_thd_stream1 & AV_CH_SIDE_LEFT &&
            mh.channel_layout_thd_stream1 & AV_CH_SIDE_RIGHT &&
            mh.channel_modifier_thd_stream1 == THD_CH_MODIFIER_SURROUNDEX)
            m->substream[1].matrix_encoding = AV_MATRIX_ENCODING_DOLBYEX;

        if (mh.num_substreams > 0)
            switch (mh.channel_modifier_thd_stream0) {
            case THD_CH_MODIFIER_LTRT:
                m->substream[0].matrix_encoding = AV_MATRIX_ENCODING_DOLBY;
                break;
            case THD_CH_MODIFIER_LBINRBIN:
                m->substream[0].matrix_encoding = AV_MATRIX_ENCODING_DOLBYHEADPHONE;
                break;
            default:
                break;
            }
    }

    return 0;
}