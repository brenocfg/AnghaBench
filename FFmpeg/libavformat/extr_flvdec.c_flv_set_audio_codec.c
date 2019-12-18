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
struct TYPE_6__ {int bits_per_coded_sample; int sample_rate; int codec_tag; void* codec_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  need_parsing; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL ; 
 void* AV_CODEC_ID_AAC ; 
 void* AV_CODEC_ID_ADPCM_SWF ; 
 void* AV_CODEC_ID_MP3 ; 
 void* AV_CODEC_ID_NELLYMOSER ; 
 void* AV_CODEC_ID_PCM_ALAW ; 
 void* AV_CODEC_ID_PCM_MULAW ; 
 void* AV_CODEC_ID_PCM_S16BE ; 
 void* AV_CODEC_ID_PCM_S16LE ; 
 void* AV_CODEC_ID_PCM_U8 ; 
 void* AV_CODEC_ID_SPEEX ; 
 int FLV_AUDIO_CODECID_OFFSET ; 
#define  FLV_CODECID_AAC 138 
#define  FLV_CODECID_ADPCM 137 
#define  FLV_CODECID_MP3 136 
#define  FLV_CODECID_NELLYMOSER 135 
#define  FLV_CODECID_NELLYMOSER_16KHZ_MONO 134 
#define  FLV_CODECID_NELLYMOSER_8KHZ_MONO 133 
#define  FLV_CODECID_PCM 132 
#define  FLV_CODECID_PCM_ALAW 131 
#define  FLV_CODECID_PCM_LE 130 
#define  FLV_CODECID_PCM_MULAW 129 
#define  FLV_CODECID_SPEEX 128 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void flv_set_audio_codec(AVFormatContext *s, AVStream *astream,
                                AVCodecParameters *apar, int flv_codecid)
{
    switch (flv_codecid) {
    // no distinction between S16 and S8 PCM codec flags
    case FLV_CODECID_PCM:
        apar->codec_id = apar->bits_per_coded_sample == 8
                           ? AV_CODEC_ID_PCM_U8
#if HAVE_BIGENDIAN
                           : AV_CODEC_ID_PCM_S16BE;
#else
                           : AV_CODEC_ID_PCM_S16LE;
#endif
        break;
    case FLV_CODECID_PCM_LE:
        apar->codec_id = apar->bits_per_coded_sample == 8
                           ? AV_CODEC_ID_PCM_U8
                           : AV_CODEC_ID_PCM_S16LE;
        break;
    case FLV_CODECID_AAC:
        apar->codec_id = AV_CODEC_ID_AAC;
        break;
    case FLV_CODECID_ADPCM:
        apar->codec_id = AV_CODEC_ID_ADPCM_SWF;
        break;
    case FLV_CODECID_SPEEX:
        apar->codec_id    = AV_CODEC_ID_SPEEX;
        apar->sample_rate = 16000;
        break;
    case FLV_CODECID_MP3:
        apar->codec_id      = AV_CODEC_ID_MP3;
        astream->need_parsing = AVSTREAM_PARSE_FULL;
        break;
    case FLV_CODECID_NELLYMOSER_8KHZ_MONO:
        // in case metadata does not otherwise declare samplerate
        apar->sample_rate = 8000;
        apar->codec_id    = AV_CODEC_ID_NELLYMOSER;
        break;
    case FLV_CODECID_NELLYMOSER_16KHZ_MONO:
        apar->sample_rate = 16000;
        apar->codec_id    = AV_CODEC_ID_NELLYMOSER;
        break;
    case FLV_CODECID_NELLYMOSER:
        apar->codec_id = AV_CODEC_ID_NELLYMOSER;
        break;
    case FLV_CODECID_PCM_MULAW:
        apar->sample_rate = 8000;
        apar->codec_id    = AV_CODEC_ID_PCM_MULAW;
        break;
    case FLV_CODECID_PCM_ALAW:
        apar->sample_rate = 8000;
        apar->codec_id    = AV_CODEC_ID_PCM_ALAW;
        break;
    default:
        avpriv_request_sample(s, "Audio codec (%x)",
               flv_codecid >> FLV_AUDIO_CODECID_OFFSET);
        apar->codec_tag = flv_codecid >> FLV_AUDIO_CODECID_OFFSET;
    }
}