#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  long long int64_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_20__ {TYPE_2__* priv_data; } ;
struct TYPE_19__ {int nb_samples; scalar_t__ extended_data; } ;
struct TYPE_18__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* bswap16_buf ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_17__ {int max_framesize; int allocated_bitstream_size; int bitstream_size; int bitstream_index; int bitindex; int blocksize; int channels; int got_quit_command; int cur_chan; unsigned int bitshift; int version; int nmean; int** offset; int nwrap; int internal_ftype; TYPE_5__* avctx; int /*<<< orphan*/  gb; TYPE_1__ bdsp; scalar_t__ swap; scalar_t__** decoded; int /*<<< orphan*/ * bitstream; int /*<<< orphan*/  got_header; } ;
typedef  TYPE_2__ ShortenContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ BITSHIFTSIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ ENERGYSIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 scalar_t__ FNSIZE ; 
#define  FN_BITSHIFT 134 
#define  FN_BLOCKSIZE 133 
#define  FN_QUIT 132 
#define  FN_VERBATIM 131 
 unsigned int FN_ZERO ; 
 unsigned int MAX_BLOCKSIZE ; 
#define  TYPE_S16HL 130 
#define  TYPE_S16LH 129 
#define  TYPE_U8 128 
 scalar_t__ VERBATIM_BYTE_SIZE ; 
 scalar_t__ VERBATIM_CKSIZE_SIZE ; 
 int /*<<< orphan*/  av_clip_int16 (scalar_t__) ; 
 int /*<<< orphan*/  av_clip_uint8 (scalar_t__) ; 
 void* av_fast_realloc (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_log2 (int) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_5__*,char*) ; 
 int decode_subframe_lpc (TYPE_2__*,unsigned int,int,int,int) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fix_bitshift (TYPE_2__*,scalar_t__*) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 unsigned int get_uint (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* get_ur_golomb_shorten (int /*<<< orphan*/ *,scalar_t__) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * is_audio_command ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int read_header (TYPE_2__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int shorten_decode_frame(AVCodecContext *avctx, void *data,
                                int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    ShortenContext *s  = avctx->priv_data;
    int i, input_buf_size = 0;
    int ret;

    /* allocate internal bitstream buffer */
    if (s->max_framesize == 0) {
        void *tmp_ptr;
        s->max_framesize = 8192; // should hopefully be enough for the first header
        tmp_ptr = av_fast_realloc(s->bitstream, &s->allocated_bitstream_size,
                                  s->max_framesize + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!tmp_ptr) {
            s->max_framesize = 0;
            av_log(avctx, AV_LOG_ERROR, "error allocating bitstream buffer\n");
            return AVERROR(ENOMEM);
        }
        memset(tmp_ptr, 0, s->allocated_bitstream_size);
        s->bitstream = tmp_ptr;
    }

    /* append current packet data to bitstream buffer */
    buf_size       = FFMIN(buf_size, s->max_framesize - s->bitstream_size);
    input_buf_size = buf_size;

    if (s->bitstream_index + s->bitstream_size + buf_size + AV_INPUT_BUFFER_PADDING_SIZE >
        s->allocated_bitstream_size) {
        memmove(s->bitstream, &s->bitstream[s->bitstream_index],
                s->bitstream_size);
        s->bitstream_index = 0;
    }
    if (buf)
        memcpy(&s->bitstream[s->bitstream_index + s->bitstream_size], buf,
               buf_size);
    buf               = &s->bitstream[s->bitstream_index];
    buf_size         += s->bitstream_size;
    s->bitstream_size = buf_size;

    /* do not decode until buffer has at least max_framesize bytes or
     * the end of the file has been reached */
    if (buf_size < s->max_framesize && avpkt->data) {
        *got_frame_ptr = 0;
        return input_buf_size;
    }
    /* init and position bitstream reader */
    if ((ret = init_get_bits8(&s->gb, buf, buf_size)) < 0)
        return ret;
    skip_bits(&s->gb, s->bitindex);

    /* process header or next subblock */
    if (!s->got_header) {

        if ((ret = read_header(s)) < 0)
            return ret;

        if (avpkt->size) {
            int max_framesize;
            void *tmp_ptr;

            max_framesize = FFMAX(s->max_framesize, s->blocksize * s->channels * 8);
            tmp_ptr = av_fast_realloc(s->bitstream, &s->allocated_bitstream_size,
                                      max_framesize + AV_INPUT_BUFFER_PADDING_SIZE);
            if (!tmp_ptr) {
                av_log(avctx, AV_LOG_ERROR, "error allocating bitstream buffer\n");
                return AVERROR(ENOMEM);
            }
            s->bitstream = tmp_ptr;
            s->max_framesize = max_framesize;
            *got_frame_ptr = 0;
            goto finish_frame;
        }
    }

    /* if quit command was read previously, don't decode anything */
    if (s->got_quit_command) {
        *got_frame_ptr = 0;
        return avpkt->size;
    }

    s->cur_chan = 0;
    while (s->cur_chan < s->channels) {
        unsigned cmd;
        int len;

        if (get_bits_left(&s->gb) < 3 + FNSIZE) {
            *got_frame_ptr = 0;
            break;
        }

        cmd = get_ur_golomb_shorten(&s->gb, FNSIZE);

        if (cmd > FN_VERBATIM) {
            av_log(avctx, AV_LOG_ERROR, "unknown shorten function %d\n", cmd);
            *got_frame_ptr = 0;
            break;
        }

        if (!is_audio_command[cmd]) {
            /* process non-audio command */
            switch (cmd) {
            case FN_VERBATIM:
                len = get_ur_golomb_shorten(&s->gb, VERBATIM_CKSIZE_SIZE);
                if (len < 0 || len > get_bits_left(&s->gb)) {
                    av_log(avctx, AV_LOG_ERROR, "verbatim length %d invalid\n",
                           len);
                    return AVERROR_INVALIDDATA;
                }
                while (len--)
                    get_ur_golomb_shorten(&s->gb, VERBATIM_BYTE_SIZE);
                break;
            case FN_BITSHIFT: {
                unsigned bitshift = get_ur_golomb_shorten(&s->gb, BITSHIFTSIZE);
                if (bitshift > 32) {
                    av_log(avctx, AV_LOG_ERROR, "bitshift %d is invalid\n",
                           bitshift);
                    return AVERROR_INVALIDDATA;
                }
                s->bitshift = bitshift;
                break;
            }
            case FN_BLOCKSIZE: {
                unsigned blocksize = get_uint(s, av_log2(s->blocksize));
                if (blocksize > s->blocksize) {
                    avpriv_report_missing_feature(avctx,
                                                  "Increasing block size");
                    return AVERROR_PATCHWELCOME;
                }
                if (!blocksize || blocksize > MAX_BLOCKSIZE) {
                    av_log(avctx, AV_LOG_ERROR, "invalid or unsupported "
                                                "block size: %d\n", blocksize);
                    return AVERROR(EINVAL);
                }
                s->blocksize = blocksize;
                break;
            }
            case FN_QUIT:
                s->got_quit_command = 1;
                break;
            }
            if (cmd == FN_QUIT)
                break;
        } else {
            /* process audio command */
            int residual_size = 0;
            int channel = s->cur_chan;
            int32_t coffset;

            /* get Rice code for residual decoding */
            if (cmd != FN_ZERO) {
                residual_size = get_ur_golomb_shorten(&s->gb, ENERGYSIZE);
                /* This is a hack as version 0 differed in the definition
                 * of get_sr_golomb_shorten(). */
                if (s->version == 0)
                    residual_size--;
                if (residual_size > 30U) {
                    av_log(avctx, AV_LOG_ERROR, "residual size unsupportd: %d\n", residual_size);
                    return AVERROR_INVALIDDATA;
                }
            }

            /* calculate sample offset using means from previous blocks */
            if (s->nmean == 0)
                coffset = s->offset[channel][0];
            else {
                int32_t sum = (s->version < 2) ? 0 : s->nmean / 2;
                for (i = 0; i < s->nmean; i++)
                    sum += (unsigned)s->offset[channel][i];
                coffset = sum / s->nmean;
                if (s->version >= 2)
                    coffset = s->bitshift == 0 ? coffset : coffset >> s->bitshift - 1 >> 1;
            }

            /* decode samples for this channel */
            if (cmd == FN_ZERO) {
                for (i = 0; i < s->blocksize; i++)
                    s->decoded[channel][i] = 0;
            } else {
                if ((ret = decode_subframe_lpc(s, cmd, channel,
                                               residual_size, coffset)) < 0)
                    return ret;
            }

            /* update means with info from the current block */
            if (s->nmean > 0) {
                int64_t sum = (s->version < 2) ? 0 : s->blocksize / 2;
                for (i = 0; i < s->blocksize; i++)
                    sum += s->decoded[channel][i];

                for (i = 1; i < s->nmean; i++)
                    s->offset[channel][i - 1] = s->offset[channel][i];

                if (s->version < 2)
                    s->offset[channel][s->nmean - 1] = sum / s->blocksize;
                else
                    s->offset[channel][s->nmean - 1] = s->bitshift == 32 ? 0 : (sum / s->blocksize) * (1LL << s->bitshift);
            }

            /* copy wrap samples for use with next block */
            for (i = -s->nwrap; i < 0; i++)
                s->decoded[channel][i] = s->decoded[channel][i + s->blocksize];

            /* shift samples to add in unused zero bits which were removed
             * during encoding */
            fix_bitshift(s, s->decoded[channel]);

            /* if this is the last channel in the block, output the samples */
            s->cur_chan++;
            if (s->cur_chan == s->channels) {
                uint8_t *samples_u8;
                int16_t *samples_s16;
                int chan;

                /* get output buffer */
                frame->nb_samples = s->blocksize;
                if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
                    return ret;

                for (chan = 0; chan < s->channels; chan++) {
                    samples_u8  = ((uint8_t **)frame->extended_data)[chan];
                    samples_s16 = ((int16_t **)frame->extended_data)[chan];
                    for (i = 0; i < s->blocksize; i++) {
                        switch (s->internal_ftype) {
                        case TYPE_U8:
                            *samples_u8++ = av_clip_uint8(s->decoded[chan][i]);
                            break;
                        case TYPE_S16HL:
                        case TYPE_S16LH:
                            *samples_s16++ = av_clip_int16(s->decoded[chan][i]);
                            break;
                        }
                    }
                    if (s->swap && s->internal_ftype != TYPE_U8)
                        s->bdsp.bswap16_buf(((uint16_t **)frame->extended_data)[chan],
                                            ((uint16_t **)frame->extended_data)[chan],
                                            s->blocksize);

                }

                *got_frame_ptr = 1;
            }
        }
    }
    if (s->cur_chan < s->channels)
        *got_frame_ptr = 0;

finish_frame:
    s->bitindex = get_bits_count(&s->gb) - 8 * (get_bits_count(&s->gb) / 8);
    i           = get_bits_count(&s->gb) / 8;
    if (i > buf_size) {
        av_log(s->avctx, AV_LOG_ERROR, "overread: %d\n", i - buf_size);
        s->bitstream_size  = 0;
        s->bitstream_index = 0;
        return AVERROR_INVALIDDATA;
    }
    if (s->bitstream_size) {
        s->bitstream_index += i;
        s->bitstream_size  -= i;
        return input_buf_size;
    } else
        return i;
}