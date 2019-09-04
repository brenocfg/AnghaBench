#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_2__* oc; TYPE_5__* avctx; } ;
struct LATMContext {scalar_t__ initialized; TYPE_6__ aac_ctx; } ;
struct TYPE_21__ {int extradata_size; int /*<<< orphan*/ * extradata; } ;
struct TYPE_20__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_19__ {scalar_t__ sample_rate; scalar_t__ chan_config; int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {scalar_t__ sample_rate; scalar_t__ chan_config; } ;
struct TYPE_18__ {TYPE_1__ m4ac; } ;
typedef  TYPE_3__ MPEG4AudioConfig ;
typedef  TYPE_4__ GetBitContext ;
typedef  TYPE_5__ AVCodecContext ;
typedef  TYPE_6__ AACContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,scalar_t__) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * av_malloc (scalar_t__) ; 
 int decode_audio_specific_config_gb (int /*<<< orphan*/ *,TYPE_5__*,TYPE_3__*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  get_bits (TYPE_4__*,int) ; 
 int get_bits_count (TYPE_4__*) ; 
 scalar_t__ get_bits_left (TYPE_4__*) ; 
 int /*<<< orphan*/  init_get_bits (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skip_bits_long (TYPE_4__*,int) ; 

__attribute__((used)) static int latm_decode_audio_specific_config(struct LATMContext *latmctx,
                                             GetBitContext *gb, int asclen)
{
    AACContext *ac        = &latmctx->aac_ctx;
    AVCodecContext *avctx = ac->avctx;
    MPEG4AudioConfig m4ac = { 0 };
    GetBitContext gbc;
    int config_start_bit  = get_bits_count(gb);
    int sync_extension    = 0;
    int bits_consumed, esize, i;

    if (asclen > 0) {
        sync_extension = 1;
        asclen         = FFMIN(asclen, get_bits_left(gb));
        init_get_bits(&gbc, gb->buffer, config_start_bit + asclen);
        skip_bits_long(&gbc, config_start_bit);
    } else if (asclen == 0) {
        gbc = *gb;
    } else {
        return AVERROR_INVALIDDATA;
    }

    if (get_bits_left(gb) <= 0)
        return AVERROR_INVALIDDATA;

    bits_consumed = decode_audio_specific_config_gb(NULL, avctx, &m4ac,
                                                    &gbc, config_start_bit,
                                                    sync_extension);

    if (bits_consumed < config_start_bit)
        return AVERROR_INVALIDDATA;
    bits_consumed -= config_start_bit;

    if (asclen == 0)
      asclen = bits_consumed;

    if (!latmctx->initialized ||
        ac->oc[1].m4ac.sample_rate != m4ac.sample_rate ||
        ac->oc[1].m4ac.chan_config != m4ac.chan_config) {

        if (latmctx->initialized) {
            av_log(avctx, AV_LOG_INFO, "audio config changed (sample_rate=%d, chan_config=%d)\n", m4ac.sample_rate, m4ac.chan_config);
        } else {
            av_log(avctx, AV_LOG_DEBUG, "initializing latmctx\n");
        }
        latmctx->initialized = 0;

        esize = (asclen + 7) / 8;

        if (avctx->extradata_size < esize) {
            av_free(avctx->extradata);
            avctx->extradata = av_malloc(esize + AV_INPUT_BUFFER_PADDING_SIZE);
            if (!avctx->extradata)
                return AVERROR(ENOMEM);
        }

        avctx->extradata_size = esize;
        gbc = *gb;
        for (i = 0; i < esize; i++) {
          avctx->extradata[i] = get_bits(&gbc, 8);
        }
        memset(avctx->extradata+esize, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    }
    skip_bits_long(gb, asclen);

    return 0;
}