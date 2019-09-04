#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  enum AVMatrixEncoding { ____Placeholder_AVMatrixEncoding } AVMatrixEncoding ;
struct TYPE_20__ {int /*<<< orphan*/  (* bswap16_buf ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ;} ;
struct TYPE_26__ {int superframe_size; int* input_buffer; int substreamid; int frame_size; scalar_t__ frame_type; int channels; int out_channels; size_t output_mode; size_t channel_mode; int lfe_on; size_t center_mix_level; size_t surround_mix_level; int fbw_channels; int bitstream_mode; int** output; int** outptr; int** output_buffer; int num_blocks; scalar_t__ sample_rate; size_t prev_output_mode; int channel_map; scalar_t__ dolby_surround_mode; scalar_t__ dolby_headphone_mode; int dolby_surround_ex_mode; int preferred_downmix; size_t center_mix_level_ltrt; size_t surround_mix_level_ltrt; size_t lfe_mix_level; scalar_t__ lfe_mix_level_exists; scalar_t__ prev_bit_rate; scalar_t__ bit_rate; int /*<<< orphan*/  gbc; void* ltrt_surround_mix_level; void* ltrt_center_mix_level; void* loro_surround_mix_level; void* loro_center_mix_level; int /*<<< orphan*/  dith_state; scalar_t__ consistent_noise_generation; TYPE_1__ bdsp; } ;
struct TYPE_25__ {scalar_t__ frame_type; int num_blocks; scalar_t__ sample_rate; } ;
struct TYPE_24__ {int err_recognition; scalar_t__ request_channel_layout; int channels; int channel_layout; int audio_service_type; scalar_t__ sample_rate; scalar_t__ bit_rate; TYPE_7__* priv_data; } ;
struct TYPE_23__ {double lfe_mix_level; void* surround_mix_level_ltrt; void* surround_mix_level; void* center_mix_level_ltrt; void* center_mix_level; int /*<<< orphan*/  preferred_downmix_type; } ;
struct TYPE_22__ {int nb_samples; scalar_t__* extended_data; scalar_t__* data; int /*<<< orphan*/  decode_error_flags; } ;
struct TYPE_21__ {int* data; int size; } ;
typedef  int SHORTFLOAT ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVDownmixInfo ;
typedef  TYPE_5__ AVCodecContext ;
typedef  TYPE_6__ AC3HeaderInfo ;
typedef  TYPE_7__ AC3DecodeContext ;

/* Variables and functions */
#define  AAC_AC3_PARSE_ERROR_BSID 139 
#define  AAC_AC3_PARSE_ERROR_CHANNEL_CFG 138 
#define  AAC_AC3_PARSE_ERROR_CRC 137 
#define  AAC_AC3_PARSE_ERROR_FRAME_SIZE 136 
#define  AAC_AC3_PARSE_ERROR_FRAME_TYPE 135 
#define  AAC_AC3_PARSE_ERROR_SAMPLE_RATE 134 
#define  AAC_AC3_PARSE_ERROR_SYNC 133 
 int AC3_BLOCK_SIZE ; 
 size_t AC3_CHMODE_2F2R ; 
 size_t AC3_CHMODE_MONO ; 
 size_t AC3_CHMODE_STEREO ; 
 scalar_t__ AC3_DHEADPHONMOD_ON ; 
#define  AC3_DMIXMOD_DPLII 132 
#define  AC3_DMIXMOD_LORO 131 
#define  AC3_DMIXMOD_LTRT 130 
#define  AC3_DSUREXMOD_ON 129 
#define  AC3_DSUREXMOD_PLIIZ 128 
 scalar_t__ AC3_DSURMOD_ON ; 
 int AC3_FRAME_BUFFER_SIZE ; 
 int AC3_MAX_CHANNELS ; 
 size_t AC3_OUTPUT_LFEON ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_AUDIO_SERVICE_TYPE_KARAOKE ; 
 scalar_t__ AV_CH_LAYOUT_MONO ; 
 scalar_t__ AV_CH_LAYOUT_STEREO ; 
 int AV_CH_LOW_FREQUENCY ; 
 int /*<<< orphan*/  AV_CRC_16_ANSI ; 
 int /*<<< orphan*/  AV_DOWNMIX_TYPE_DPLII ; 
 int /*<<< orphan*/  AV_DOWNMIX_TYPE_LORO ; 
 int /*<<< orphan*/  AV_DOWNMIX_TYPE_LTRT ; 
 int /*<<< orphan*/  AV_DOWNMIX_TYPE_UNKNOWN ; 
 int AV_EF_CAREFUL ; 
 int AV_EF_CRCCHECK ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_MATRIX_ENCODING_DOLBY ; 
 int AV_MATRIX_ENCODING_DOLBYEX ; 
 int AV_MATRIX_ENCODING_DOLBYHEADPHONE ; 
 int AV_MATRIX_ENCODING_DPLIIZ ; 
 int AV_MATRIX_ENCODING_NONE ; 
 int AV_NUM_DATA_POINTERS ; 
 int AV_RB16 (int const*) ; 
 scalar_t__ EAC3_FRAME_TYPE_DEPENDENT ; 
 int EAC3_MAX_CHANNELS ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  FF_DECODE_ERROR_INVALID_BITSTREAM ; 
 void* LEVEL_MINUS_3DB ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ av_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  av_crc_get_table (int /*<<< orphan*/ ) ; 
 TYPE_4__* av_downmix_info_update_side_data (TYPE_3__*) ; 
 int av_get_channel_layout_channel_index (int,unsigned long long) ; 
 int av_get_channel_layout_nb_channels (int) ; 
 int /*<<< orphan*/  av_lfg_init_from_data (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 void** avpriv_ac3_channel_layout_tab ; 
 scalar_t__ decode_audio_block (TYPE_7__*,int,int) ; 
 int* ff_ac3_channels_tab ; 
 int*** ff_ac3_dec_channel_map ; 
 int ff_ac3_parse_header (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int** ff_eac3_custom_channel_map_locations ; 
 int ff_get_buffer (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_side_data_update_matrix_encoding (TYPE_3__*,int) ; 
 void** gain_levels ; 
 double* gain_levels_lfe ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int parse_frame_header (TYPE_7__*) ; 
 int set_downmix_coeffs (TYPE_7__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int ac3_decode_frame(AVCodecContext * avctx, void *data,
                            int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size, full_buf_size = avpkt->size;
    AC3DecodeContext *s = avctx->priv_data;
    int blk, ch, err, offset, ret;
    int i;
    int skip = 0, got_independent_frame = 0;
    const uint8_t *channel_map;
    uint8_t extended_channel_map[EAC3_MAX_CHANNELS];
    const SHORTFLOAT *output[AC3_MAX_CHANNELS];
    enum AVMatrixEncoding matrix_encoding;
    AVDownmixInfo *downmix_info;

    s->superframe_size = 0;

    buf_size = full_buf_size;
    for (i = 1; i < buf_size; i += 2) {
        if (buf[i] == 0x77 || buf[i] == 0x0B) {
            if ((buf[i] ^ buf[i-1]) == (0x77 ^ 0x0B)) {
                i--;
                break;
            } else if ((buf[i] ^ buf[i+1]) == (0x77 ^ 0x0B)) {
                break;
            }
        }
    }
    if (i >= buf_size)
        return AVERROR_INVALIDDATA;
    if (i > 10)
        return i;
    buf += i;
    buf_size -= i;

    /* copy input buffer to decoder context to avoid reading past the end
       of the buffer, which can be caused by a damaged input stream. */
    if (buf_size >= 2 && AV_RB16(buf) == 0x770B) {
        // seems to be byte-swapped AC-3
        int cnt = FFMIN(buf_size, AC3_FRAME_BUFFER_SIZE) >> 1;
        s->bdsp.bswap16_buf((uint16_t *) s->input_buffer,
                            (const uint16_t *) buf, cnt);
    } else
        memcpy(s->input_buffer, buf, FFMIN(buf_size, AC3_FRAME_BUFFER_SIZE));

    /* if consistent noise generation is enabled, seed the linear feedback generator
     * with the contents of the AC-3 frame so that the noise is identical across
     * decodes given the same AC-3 frame data, for use with non-linear edititing software. */
    if (s->consistent_noise_generation)
        av_lfg_init_from_data(&s->dith_state, s->input_buffer, FFMIN(buf_size, AC3_FRAME_BUFFER_SIZE));

    buf = s->input_buffer;
dependent_frame:
    /* initialize the GetBitContext with the start of valid AC-3 Frame */
    if ((ret = init_get_bits8(&s->gbc, buf, buf_size)) < 0)
        return ret;

    /* parse the syncinfo */
    err = parse_frame_header(s);

    if (err) {
        switch (err) {
        case AAC_AC3_PARSE_ERROR_SYNC:
            av_log(avctx, AV_LOG_ERROR, "frame sync error\n");
            return AVERROR_INVALIDDATA;
        case AAC_AC3_PARSE_ERROR_BSID:
            av_log(avctx, AV_LOG_ERROR, "invalid bitstream id\n");
            break;
        case AAC_AC3_PARSE_ERROR_SAMPLE_RATE:
            av_log(avctx, AV_LOG_ERROR, "invalid sample rate\n");
            break;
        case AAC_AC3_PARSE_ERROR_FRAME_SIZE:
            av_log(avctx, AV_LOG_ERROR, "invalid frame size\n");
            break;
        case AAC_AC3_PARSE_ERROR_FRAME_TYPE:
            /* skip frame if CRC is ok. otherwise use error concealment. */
            /* TODO: add support for substreams */
            if (s->substreamid) {
                av_log(avctx, AV_LOG_DEBUG,
                       "unsupported substream %d: skipping frame\n",
                       s->substreamid);
                *got_frame_ptr = 0;
                return buf_size;
            } else {
                av_log(avctx, AV_LOG_ERROR, "invalid frame type\n");
            }
            break;
        case AAC_AC3_PARSE_ERROR_CRC:
        case AAC_AC3_PARSE_ERROR_CHANNEL_CFG:
            break;
        default: // Normal AVERROR do not try to recover.
            *got_frame_ptr = 0;
            return err;
        }
    } else {
        /* check that reported frame size fits in input buffer */
        if (s->frame_size > buf_size) {
            av_log(avctx, AV_LOG_ERROR, "incomplete frame\n");
            err = AAC_AC3_PARSE_ERROR_FRAME_SIZE;
        } else if (avctx->err_recognition & (AV_EF_CRCCHECK|AV_EF_CAREFUL)) {
            /* check for crc mismatch */
            if (av_crc(av_crc_get_table(AV_CRC_16_ANSI), 0, &buf[2],
                       s->frame_size - 2)) {
                av_log(avctx, AV_LOG_ERROR, "frame CRC mismatch\n");
                if (avctx->err_recognition & AV_EF_EXPLODE)
                    return AVERROR_INVALIDDATA;
                err = AAC_AC3_PARSE_ERROR_CRC;
            }
        }
    }

    if (s->frame_type == EAC3_FRAME_TYPE_DEPENDENT && !got_independent_frame) {
        av_log(avctx, AV_LOG_WARNING, "Ignoring dependent frame without independent frame.\n");
        *got_frame_ptr = 0;
        return FFMIN(full_buf_size, s->frame_size);
    }

    /* channel config */
    if (!err || (s->channels && s->out_channels != s->channels)) {
        s->out_channels = s->channels;
        s->output_mode  = s->channel_mode;
        if (s->lfe_on)
            s->output_mode |= AC3_OUTPUT_LFEON;
        if (s->channels > 1 &&
            avctx->request_channel_layout == AV_CH_LAYOUT_MONO) {
            s->out_channels = 1;
            s->output_mode  = AC3_CHMODE_MONO;
        } else if (s->channels > 2 &&
                   avctx->request_channel_layout == AV_CH_LAYOUT_STEREO) {
            s->out_channels = 2;
            s->output_mode  = AC3_CHMODE_STEREO;
        }

        s->loro_center_mix_level   = gain_levels[s->  center_mix_level];
        s->loro_surround_mix_level = gain_levels[s->surround_mix_level];
        s->ltrt_center_mix_level   = LEVEL_MINUS_3DB;
        s->ltrt_surround_mix_level = LEVEL_MINUS_3DB;
        /* set downmixing coefficients if needed */
        if (s->channels != s->out_channels && !((s->output_mode & AC3_OUTPUT_LFEON) &&
                s->fbw_channels == s->out_channels)) {
            if ((ret = set_downmix_coeffs(s)) < 0) {
                av_log(avctx, AV_LOG_ERROR, "error setting downmix coeffs\n");
                return ret;
            }
        }
    } else if (!s->channels) {
        av_log(avctx, AV_LOG_ERROR, "unable to determine channel mode\n");
        return AVERROR_INVALIDDATA;
    }
    avctx->channels = s->out_channels;
    avctx->channel_layout = avpriv_ac3_channel_layout_tab[s->output_mode & ~AC3_OUTPUT_LFEON];
    if (s->output_mode & AC3_OUTPUT_LFEON)
        avctx->channel_layout |= AV_CH_LOW_FREQUENCY;

    /* set audio service type based on bitstream mode for AC-3 */
    avctx->audio_service_type = s->bitstream_mode;
    if (s->bitstream_mode == 0x7 && s->channels > 1)
        avctx->audio_service_type = AV_AUDIO_SERVICE_TYPE_KARAOKE;

    /* decode the audio blocks */
    channel_map = ff_ac3_dec_channel_map[s->output_mode & ~AC3_OUTPUT_LFEON][s->lfe_on];
    offset = s->frame_type == EAC3_FRAME_TYPE_DEPENDENT ? AC3_MAX_CHANNELS : 0;
    for (ch = 0; ch < AC3_MAX_CHANNELS; ch++) {
        output[ch] = s->output[ch + offset];
        s->outptr[ch] = s->output[ch + offset];
    }
    for (ch = 0; ch < s->channels; ch++) {
        if (ch < s->out_channels)
            s->outptr[channel_map[ch]] = s->output_buffer[ch + offset];
    }
    for (blk = 0; blk < s->num_blocks; blk++) {
        if (!err && decode_audio_block(s, blk, offset)) {
            av_log(avctx, AV_LOG_ERROR, "error decoding the audio block\n");
            err = 1;
        }
        if (err)
            for (ch = 0; ch < s->out_channels; ch++)
                memcpy(s->output_buffer[ch + offset] + AC3_BLOCK_SIZE*blk, output[ch], AC3_BLOCK_SIZE*sizeof(SHORTFLOAT));
        for (ch = 0; ch < s->out_channels; ch++)
            output[ch] = s->outptr[channel_map[ch]];
        for (ch = 0; ch < s->out_channels; ch++) {
            if (!ch || channel_map[ch])
                s->outptr[channel_map[ch]] += AC3_BLOCK_SIZE;
        }
    }

    /* keep last block for error concealment in next frame */
    for (ch = 0; ch < s->out_channels; ch++)
        memcpy(s->output[ch + offset], output[ch], AC3_BLOCK_SIZE*sizeof(SHORTFLOAT));

    /* check if there is dependent frame */
    if (buf_size > s->frame_size) {
        AC3HeaderInfo hdr;
        int err;

        if (buf_size - s->frame_size <= 16) {
            skip = buf_size - s->frame_size;
            goto skip;
        }

        if ((ret = init_get_bits8(&s->gbc, buf + s->frame_size, buf_size - s->frame_size)) < 0)
            return ret;

        err = ff_ac3_parse_header(&s->gbc, &hdr);
        if (err)
            return err;

        if (hdr.frame_type == EAC3_FRAME_TYPE_DEPENDENT) {
            if (hdr.num_blocks != s->num_blocks || s->sample_rate != hdr.sample_rate) {
                av_log(avctx, AV_LOG_WARNING, "Ignoring non-compatible dependent frame.\n");
            } else {
                buf += s->frame_size;
                buf_size -= s->frame_size;
                s->prev_output_mode = s->output_mode;
                s->prev_bit_rate = s->bit_rate;
                got_independent_frame = 1;
                goto dependent_frame;
            }
        }
    }
skip:

    frame->decode_error_flags = err ? FF_DECODE_ERROR_INVALID_BITSTREAM : 0;

    /* if frame is ok, set audio parameters */
    if (!err) {
        avctx->sample_rate = s->sample_rate;
        avctx->bit_rate    = s->bit_rate + s->prev_bit_rate;
    }

    for (ch = 0; ch < EAC3_MAX_CHANNELS; ch++)
        extended_channel_map[ch] = ch;

    if (s->frame_type == EAC3_FRAME_TYPE_DEPENDENT) {
        uint64_t ich_layout = avpriv_ac3_channel_layout_tab[s->prev_output_mode & ~AC3_OUTPUT_LFEON];
        int channel_map_size = ff_ac3_channels_tab[s->output_mode & ~AC3_OUTPUT_LFEON] + s->lfe_on;
        uint64_t channel_layout;
        int extend = 0;

        if (s->prev_output_mode & AC3_OUTPUT_LFEON)
            ich_layout |= AV_CH_LOW_FREQUENCY;

        channel_layout = ich_layout;
        for (ch = 0; ch < 16; ch++) {
            if (s->channel_map & (1 << (EAC3_MAX_CHANNELS - ch - 1))) {
                channel_layout |= ff_eac3_custom_channel_map_locations[ch][1];
            }
        }
        if (av_get_channel_layout_nb_channels(channel_layout) > EAC3_MAX_CHANNELS) {
            av_log(avctx, AV_LOG_ERROR, "Too many channels (%d) coded\n",
                   av_get_channel_layout_nb_channels(channel_layout));
            return AVERROR_INVALIDDATA;
        }

        avctx->channel_layout = channel_layout;
        avctx->channels = av_get_channel_layout_nb_channels(channel_layout);

        for (ch = 0; ch < EAC3_MAX_CHANNELS; ch++) {
            if (s->channel_map & (1 << (EAC3_MAX_CHANNELS - ch - 1))) {
                if (ff_eac3_custom_channel_map_locations[ch][0]) {
                    int index = av_get_channel_layout_channel_index(channel_layout,
                                                                    ff_eac3_custom_channel_map_locations[ch][1]);
                    if (index < 0)
                        return AVERROR_INVALIDDATA;
                    if (extend >= channel_map_size)
                        return AVERROR_INVALIDDATA;

                    extended_channel_map[index] = offset + channel_map[extend++];
                } else {
                    int i;

                    for (i = 0; i < 64; i++) {
                        if ((1ULL << i) & ff_eac3_custom_channel_map_locations[ch][1]) {
                            int index = av_get_channel_layout_channel_index(channel_layout,
                                                                            1ULL << i);
                            if (index < 0)
                                return AVERROR_INVALIDDATA;
                            if (extend >= channel_map_size)
                                return AVERROR_INVALIDDATA;

                            extended_channel_map[index] = offset + channel_map[extend++];
                        }
                    }
                }
            }
        }
    }

    /* get output buffer */
    frame->nb_samples = s->num_blocks * AC3_BLOCK_SIZE;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    for (ch = 0; ch < avctx->channels; ch++) {
        int map = extended_channel_map[ch];
        av_assert0(ch>=AV_NUM_DATA_POINTERS || frame->extended_data[ch] == frame->data[ch]);
        memcpy((SHORTFLOAT *)frame->extended_data[ch],
               s->output_buffer[map],
               s->num_blocks * AC3_BLOCK_SIZE * sizeof(SHORTFLOAT));
    }

    /*
     * AVMatrixEncoding
     *
     * Check whether the input layout is compatible, and make sure we're not
     * downmixing (else the matrix encoding is no longer applicable).
     */
    matrix_encoding = AV_MATRIX_ENCODING_NONE;
    if (s->channel_mode == AC3_CHMODE_STEREO &&
        s->channel_mode == (s->output_mode & ~AC3_OUTPUT_LFEON)) {
        if (s->dolby_surround_mode == AC3_DSURMOD_ON)
            matrix_encoding = AV_MATRIX_ENCODING_DOLBY;
        else if (s->dolby_headphone_mode == AC3_DHEADPHONMOD_ON)
            matrix_encoding = AV_MATRIX_ENCODING_DOLBYHEADPHONE;
    } else if (s->channel_mode >= AC3_CHMODE_2F2R &&
               s->channel_mode == (s->output_mode & ~AC3_OUTPUT_LFEON)) {
        switch (s->dolby_surround_ex_mode) {
        case AC3_DSUREXMOD_ON: // EX or PLIIx
            matrix_encoding = AV_MATRIX_ENCODING_DOLBYEX;
            break;
        case AC3_DSUREXMOD_PLIIZ:
            matrix_encoding = AV_MATRIX_ENCODING_DPLIIZ;
            break;
        default: // not indicated or off
            break;
        }
    }
    if ((ret = ff_side_data_update_matrix_encoding(frame, matrix_encoding)) < 0)
        return ret;

    /* AVDownmixInfo */
    if ((downmix_info = av_downmix_info_update_side_data(frame))) {
        switch (s->preferred_downmix) {
        case AC3_DMIXMOD_LTRT:
            downmix_info->preferred_downmix_type = AV_DOWNMIX_TYPE_LTRT;
            break;
        case AC3_DMIXMOD_LORO:
            downmix_info->preferred_downmix_type = AV_DOWNMIX_TYPE_LORO;
            break;
        case AC3_DMIXMOD_DPLII:
            downmix_info->preferred_downmix_type = AV_DOWNMIX_TYPE_DPLII;
            break;
        default:
            downmix_info->preferred_downmix_type = AV_DOWNMIX_TYPE_UNKNOWN;
            break;
        }
        downmix_info->center_mix_level        = gain_levels[s->       center_mix_level];
        downmix_info->center_mix_level_ltrt   = gain_levels[s->  center_mix_level_ltrt];
        downmix_info->surround_mix_level      = gain_levels[s->     surround_mix_level];
        downmix_info->surround_mix_level_ltrt = gain_levels[s->surround_mix_level_ltrt];
        if (s->lfe_mix_level_exists)
            downmix_info->lfe_mix_level       = gain_levels_lfe[s->lfe_mix_level];
        else
            downmix_info->lfe_mix_level       = 0.0; // -inf dB
    } else
        return AVERROR(ENOMEM);

    *got_frame_ptr = 1;

    if (!s->superframe_size)
        return FFMIN(full_buf_size, s->frame_size + skip);

    return FFMIN(full_buf_size, s->superframe_size + skip);
}