#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  need_parsing; TYPE_1__* codecpar; } ;
struct TYPE_10__ {int /*<<< orphan*/  fc; int /*<<< orphan*/  dv_demux; int /*<<< orphan*/  dv_fctx; } ;
struct TYPE_9__ {int time_scale; int dv_audio_container; int samples_per_frame; int bytes_per_frame; } ;
struct TYPE_8__ {scalar_t__ codec_type; int sample_rate; int codec_id; int channels; int block_align; int extradata_size; int /*<<< orphan*/  extradata; int /*<<< orphan*/  codec_tag; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  TYPE_3__ MOVContext ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL ; 
#define  AV_CODEC_ID_AC3 147 
#define  AV_CODEC_ID_ADPCM_IMA_WAV 146 
#define  AV_CODEC_ID_ADPCM_MS 145 
#define  AV_CODEC_ID_ALAC 144 
#define  AV_CODEC_ID_AMR_NB 143 
#define  AV_CODEC_ID_AMR_WB 142 
#define  AV_CODEC_ID_DVAUDIO 141 
#define  AV_CODEC_ID_EAC3 140 
#define  AV_CODEC_ID_GSM 139 
#define  AV_CODEC_ID_ILBC 138 
#define  AV_CODEC_ID_MACE3 137 
#define  AV_CODEC_ID_MACE6 136 
#define  AV_CODEC_ID_MP2 135 
#define  AV_CODEC_ID_MP3 134 
#define  AV_CODEC_ID_MPEG1VIDEO 133 
 int AV_CODEC_ID_PCM_S16LE ; 
#define  AV_CODEC_ID_QCELP 132 
#define  AV_CODEC_ID_QDM2 131 
#define  AV_CODEC_ID_VC1 130 
#define  AV_CODEC_ID_VP8 129 
#define  AV_CODEC_ID_VP9 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB32 (int /*<<< orphan*/ ) ; 
 int AV_RB8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avformat_alloc_context () ; 
 int /*<<< orphan*/  avpriv_dv_init_demux (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_finalize_stsd_codec(MOVContext *c, AVIOContext *pb,
                                   AVStream *st, MOVStreamContext *sc)
{
    if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO &&
        !st->codecpar->sample_rate && sc->time_scale > 1)
        st->codecpar->sample_rate = sc->time_scale;

    /* special codec parameters handling */
    switch (st->codecpar->codec_id) {
#if CONFIG_DV_DEMUXER
    case AV_CODEC_ID_DVAUDIO:
        c->dv_fctx = avformat_alloc_context();
        if (!c->dv_fctx) {
            av_log(c->fc, AV_LOG_ERROR, "dv demux context alloc error\n");
            return AVERROR(ENOMEM);
        }
        c->dv_demux = avpriv_dv_init_demux(c->dv_fctx);
        if (!c->dv_demux) {
            av_log(c->fc, AV_LOG_ERROR, "dv demux context init error\n");
            return AVERROR(ENOMEM);
        }
        sc->dv_audio_container = 1;
        st->codecpar->codec_id    = AV_CODEC_ID_PCM_S16LE;
        break;
#endif
    /* no ifdef since parameters are always those */
    case AV_CODEC_ID_QCELP:
        st->codecpar->channels = 1;
        // force sample rate for qcelp when not stored in mov
        if (st->codecpar->codec_tag != MKTAG('Q','c','l','p'))
            st->codecpar->sample_rate = 8000;
        // FIXME: Why is the following needed for some files?
        sc->samples_per_frame = 160;
        if (!sc->bytes_per_frame)
            sc->bytes_per_frame = 35;
        break;
    case AV_CODEC_ID_AMR_NB:
        st->codecpar->channels    = 1;
        /* force sample rate for amr, stsd in 3gp does not store sample rate */
        st->codecpar->sample_rate = 8000;
        break;
    case AV_CODEC_ID_AMR_WB:
        st->codecpar->channels    = 1;
        st->codecpar->sample_rate = 16000;
        break;
    case AV_CODEC_ID_MP2:
    case AV_CODEC_ID_MP3:
        /* force type after stsd for m1a hdlr */
        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        break;
    case AV_CODEC_ID_GSM:
    case AV_CODEC_ID_ADPCM_MS:
    case AV_CODEC_ID_ADPCM_IMA_WAV:
    case AV_CODEC_ID_ILBC:
    case AV_CODEC_ID_MACE3:
    case AV_CODEC_ID_MACE6:
    case AV_CODEC_ID_QDM2:
        st->codecpar->block_align = sc->bytes_per_frame;
        break;
    case AV_CODEC_ID_ALAC:
        if (st->codecpar->extradata_size == 36) {
            st->codecpar->channels    = AV_RB8 (st->codecpar->extradata + 21);
            st->codecpar->sample_rate = AV_RB32(st->codecpar->extradata + 32);
        }
        break;
    case AV_CODEC_ID_AC3:
    case AV_CODEC_ID_EAC3:
    case AV_CODEC_ID_MPEG1VIDEO:
    case AV_CODEC_ID_VC1:
    case AV_CODEC_ID_VP8:
    case AV_CODEC_ID_VP9:
        st->need_parsing = AVSTREAM_PARSE_FULL;
        break;
    default:
        break;
    }
    return 0;
}