#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int nuv_frametype ;
struct TYPE_6__ {int codec_id; void* bits_per_coded_sample; void* codec_tag; int /*<<< orphan*/  channel_layout; void* channels; void* sample_rate; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; } ;
struct TYPE_5__ {int /*<<< orphan*/  need_parsing; TYPE_4__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL ; 
 int AV_CODEC_ID_NONE ; 
 int AV_CODEC_ID_NUV ; 
 int AV_CODEC_ID_PCM_S16LE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* MKTAG (char,char,char,char) ; 
#define  NUV_EXTRADATA 130 
#define  NUV_MYTHEXT 129 
#define  NUV_SEEKP 128 
 int PKTSIZE (void*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 void* avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_codec_bmp_tags ; 
 void* ff_codec_get_id (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ff_get_extradata (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int ff_get_pcm_codec_id (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ff_wav_codec_get_id (void*,void*) ; 
 int /*<<< orphan*/  nuv_audio_tags ; 

__attribute__((used)) static int get_codec_data(AVFormatContext *s, AVIOContext *pb, AVStream *vst,
                          AVStream *ast, int myth)
{
    nuv_frametype frametype;

    if (!vst && !myth)
        return 1; // no codec data needed
    while (!avio_feof(pb)) {
        int size, subtype;

        frametype = avio_r8(pb);
        switch (frametype) {
        case NUV_EXTRADATA:
            subtype = avio_r8(pb);
            avio_skip(pb, 6);
            size = PKTSIZE(avio_rl32(pb));
            if (vst && subtype == 'R') {
                if (vst->codecpar->extradata) {
                    av_freep(&vst->codecpar->extradata);
                    vst->codecpar->extradata_size = 0;
                }
                if (ff_get_extradata(NULL, vst->codecpar, pb, size) < 0)
                    return AVERROR(ENOMEM);
                size = 0;
                if (!myth)
                    return 0;
            }
            break;
        case NUV_MYTHEXT:
            avio_skip(pb, 7);
            size = PKTSIZE(avio_rl32(pb));
            if (size != 128 * 4)
                break;
            avio_rl32(pb); // version
            if (vst) {
                vst->codecpar->codec_tag = avio_rl32(pb);
                vst->codecpar->codec_id =
                    ff_codec_get_id(ff_codec_bmp_tags, vst->codecpar->codec_tag);
                if (vst->codecpar->codec_tag == MKTAG('R', 'J', 'P', 'G'))
                    vst->codecpar->codec_id = AV_CODEC_ID_NUV;
            } else
                avio_skip(pb, 4);

            if (ast) {
                int id;

                ast->codecpar->codec_tag             = avio_rl32(pb);
                ast->codecpar->sample_rate           = avio_rl32(pb);
                if (ast->codecpar->sample_rate <= 0) {
                    av_log(s, AV_LOG_ERROR, "Invalid sample rate %d\n", ast->codecpar->sample_rate);
                    return AVERROR_INVALIDDATA;
                }
                ast->codecpar->bits_per_coded_sample = avio_rl32(pb);
                ast->codecpar->channels              = avio_rl32(pb);
                ast->codecpar->channel_layout        = 0;

                id = ff_wav_codec_get_id(ast->codecpar->codec_tag,
                                         ast->codecpar->bits_per_coded_sample);
                if (id == AV_CODEC_ID_NONE) {
                    id = ff_codec_get_id(nuv_audio_tags, ast->codecpar->codec_tag);
                    if (id == AV_CODEC_ID_PCM_S16LE)
                        id = ff_get_pcm_codec_id(ast->codecpar->bits_per_coded_sample,
                                                 0, 0, ~1);
                }
                ast->codecpar->codec_id = id;

                ast->need_parsing = AVSTREAM_PARSE_FULL;
            } else
                avio_skip(pb, 4 * 4);

            size -= 6 * 4;
            avio_skip(pb, size);
            return 0;
        case NUV_SEEKP:
            size = 11;
            break;
        default:
            avio_skip(pb, 7);
            size = PKTSIZE(avio_rl32(pb));
            break;
        }
        avio_skip(pb, size);
    }

    return 0;
}