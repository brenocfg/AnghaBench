#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_17__ {int /*<<< orphan*/  value; } ;
struct TYPE_16__ {TYPE_1__* codecpar; int /*<<< orphan*/  need_parsing; } ;
struct TYPE_15__ {int /*<<< orphan*/  isom; TYPE_10__* fc; } ;
struct TYPE_14__ {int audio_cid; scalar_t__ stsd_version; int samples_per_frame; int bytes_per_frame; scalar_t__ format; int sample_size; } ;
struct TYPE_13__ {int channels; int bits_per_coded_sample; int sample_rate; scalar_t__ codec_tag; int codec_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  TYPE_3__ MOVContext ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL ; 
#define  AV_CODEC_ID_ADPCM_IMA_QT 137 
#define  AV_CODEC_ID_GSM 136 
#define  AV_CODEC_ID_MACE3 135 
#define  AV_CODEC_ID_MACE6 134 
#define  AV_CODEC_ID_MP2 133 
#define  AV_CODEC_ID_MP3 132 
#define  AV_CODEC_ID_PCM_S16BE 131 
#define  AV_CODEC_ID_PCM_S16LE 130 
 int AV_CODEC_ID_PCM_S24BE ; 
 int AV_CODEC_ID_PCM_S24LE ; 
 int const AV_CODEC_ID_PCM_S32BE ; 
 int const AV_CODEC_ID_PCM_S32LE ; 
#define  AV_CODEC_ID_PCM_S8 129 
#define  AV_CODEC_ID_PCM_U8 128 
 int /*<<< orphan*/  AV_DICT_MATCH_CASE ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 TYPE_5__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int av_get_bits_per_sample (int const) ; 
 int av_int2double (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_10__*,int /*<<< orphan*/ ,char*,int,...) ; 
 void* avio_rb16 (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb64 (int /*<<< orphan*/ *) ; 
 int ff_mov_get_lpcm_codec_id (int,int) ; 
 void* mov_codec_id (TYPE_4__*,scalar_t__) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mov_parse_stsd_audio(MOVContext *c, AVIOContext *pb,
                                 AVStream *st, MOVStreamContext *sc)
{
    int bits_per_sample, flags;
    uint16_t version = avio_rb16(pb);
    AVDictionaryEntry *compatible_brands = av_dict_get(c->fc->metadata, "compatible_brands", NULL, AV_DICT_MATCH_CASE);

    avio_rb16(pb); /* revision level */
    avio_rb32(pb); /* vendor */

    st->codecpar->channels              = avio_rb16(pb); /* channel count */
    st->codecpar->bits_per_coded_sample = avio_rb16(pb); /* sample size */
    av_log(c->fc, AV_LOG_TRACE, "audio channels %d\n", st->codecpar->channels);

    sc->audio_cid = avio_rb16(pb);
    avio_rb16(pb); /* packet size = 0 */

    st->codecpar->sample_rate = ((avio_rb32(pb) >> 16));

    // Read QT version 1 fields. In version 0 these do not exist.
    av_log(c->fc, AV_LOG_TRACE, "version =%d, isom =%d\n", version, c->isom);
    if (!c->isom ||
        (compatible_brands && strstr(compatible_brands->value, "qt  ")) ||
        (sc->stsd_version == 0 && version > 0)) {
        if (version == 1) {
            sc->samples_per_frame = avio_rb32(pb);
            avio_rb32(pb); /* bytes per packet */
            sc->bytes_per_frame = avio_rb32(pb);
            avio_rb32(pb); /* bytes per sample */
        } else if (version == 2) {
            avio_rb32(pb); /* sizeof struct only */
            st->codecpar->sample_rate = av_int2double(avio_rb64(pb));
            st->codecpar->channels    = avio_rb32(pb);
            avio_rb32(pb); /* always 0x7F000000 */
            st->codecpar->bits_per_coded_sample = avio_rb32(pb);

            flags = avio_rb32(pb); /* lpcm format specific flag */
            sc->bytes_per_frame   = avio_rb32(pb);
            sc->samples_per_frame = avio_rb32(pb);
            if (st->codecpar->codec_tag == MKTAG('l','p','c','m'))
                st->codecpar->codec_id =
                    ff_mov_get_lpcm_codec_id(st->codecpar->bits_per_coded_sample,
                                             flags);
        }
        if (version == 0 || (version == 1 && sc->audio_cid != -2)) {
            /* can't correctly handle variable sized packet as audio unit */
            switch (st->codecpar->codec_id) {
            case AV_CODEC_ID_MP2:
            case AV_CODEC_ID_MP3:
                st->need_parsing = AVSTREAM_PARSE_FULL;
                break;
            }
        }
    }

    if (sc->format == 0) {
        if (st->codecpar->bits_per_coded_sample == 8)
            st->codecpar->codec_id = mov_codec_id(st, MKTAG('r','a','w',' '));
        else if (st->codecpar->bits_per_coded_sample == 16)
            st->codecpar->codec_id = mov_codec_id(st, MKTAG('t','w','o','s'));
    }

    switch (st->codecpar->codec_id) {
    case AV_CODEC_ID_PCM_S8:
    case AV_CODEC_ID_PCM_U8:
        if (st->codecpar->bits_per_coded_sample == 16)
            st->codecpar->codec_id = AV_CODEC_ID_PCM_S16BE;
        break;
    case AV_CODEC_ID_PCM_S16LE:
    case AV_CODEC_ID_PCM_S16BE:
        if (st->codecpar->bits_per_coded_sample == 8)
            st->codecpar->codec_id = AV_CODEC_ID_PCM_S8;
        else if (st->codecpar->bits_per_coded_sample == 24)
            st->codecpar->codec_id =
                st->codecpar->codec_id == AV_CODEC_ID_PCM_S16BE ?
                AV_CODEC_ID_PCM_S24BE : AV_CODEC_ID_PCM_S24LE;
        else if (st->codecpar->bits_per_coded_sample == 32)
             st->codecpar->codec_id =
                st->codecpar->codec_id == AV_CODEC_ID_PCM_S16BE ?
                AV_CODEC_ID_PCM_S32BE : AV_CODEC_ID_PCM_S32LE;
        break;
    /* set values for old format before stsd version 1 appeared */
    case AV_CODEC_ID_MACE3:
        sc->samples_per_frame = 6;
        sc->bytes_per_frame   = 2 * st->codecpar->channels;
        break;
    case AV_CODEC_ID_MACE6:
        sc->samples_per_frame = 6;
        sc->bytes_per_frame   = 1 * st->codecpar->channels;
        break;
    case AV_CODEC_ID_ADPCM_IMA_QT:
        sc->samples_per_frame = 64;
        sc->bytes_per_frame   = 34 * st->codecpar->channels;
        break;
    case AV_CODEC_ID_GSM:
        sc->samples_per_frame = 160;
        sc->bytes_per_frame   = 33;
        break;
    default:
        break;
    }

    bits_per_sample = av_get_bits_per_sample(st->codecpar->codec_id);
    if (bits_per_sample) {
        st->codecpar->bits_per_coded_sample = bits_per_sample;
        sc->sample_size = (bits_per_sample >> 3) * st->codecpar->channels;
    }
}