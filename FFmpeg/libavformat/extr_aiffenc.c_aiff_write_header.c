#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_12__ {int audio_stream_idx; void* ssnd; void* frames; void* form; } ;
struct TYPE_11__ {scalar_t__ codec_type; scalar_t__ codec_tag; int block_align; int channels; int bits_per_coded_sample; int extradata_size; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  extradata; int /*<<< orphan*/  codec_id; scalar_t__ channel_layout; } ;
struct TYPE_10__ {int nb_streams; TYPE_1__** streams; int /*<<< orphan*/ * pb; TYPE_4__* priv_data; } ;
struct TYPE_9__ {TYPE_3__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVCodecParameters ;
typedef  TYPE_4__ AIFFOutputContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int UINT64_C (int) ; 
 int av_double2int (int /*<<< orphan*/ ) ; 
 int av_get_bits_per_sample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 void* avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mov_write_chan (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  put_meta (TYPE_2__*,char*,scalar_t__) ; 

__attribute__((used)) static int aiff_write_header(AVFormatContext *s)
{
    AIFFOutputContext *aiff = s->priv_data;
    AVIOContext *pb = s->pb;
    AVCodecParameters *par;
    uint64_t sample_rate;
    int i, aifc = 0;

    aiff->audio_stream_idx = -1;
    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        if (aiff->audio_stream_idx < 0 && st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            aiff->audio_stream_idx = i;
        } else if (st->codecpar->codec_type != AVMEDIA_TYPE_VIDEO) {
            av_log(s, AV_LOG_ERROR, "AIFF allows only one audio stream and a picture.\n");
            return AVERROR(EINVAL);
        }
    }
    if (aiff->audio_stream_idx < 0) {
        av_log(s, AV_LOG_ERROR, "No audio stream present.\n");
        return AVERROR(EINVAL);
    }

    par = s->streams[aiff->audio_stream_idx]->codecpar;

    /* First verify if format is ok */
    if (!par->codec_tag)
        return AVERROR(EINVAL);
    if (par->codec_tag != MKTAG('N','O','N','E'))
        aifc = 1;

    /* FORM AIFF header */
    ffio_wfourcc(pb, "FORM");
    aiff->form = avio_tell(pb);
    avio_wb32(pb, 0);                    /* file length */
    ffio_wfourcc(pb, aifc ? "AIFC" : "AIFF");

    if (aifc) { // compressed audio
        if (!par->block_align) {
            av_log(s, AV_LOG_ERROR, "block align not set\n");
            return AVERROR(EINVAL);
        }
        /* Version chunk */
        ffio_wfourcc(pb, "FVER");
        avio_wb32(pb, 4);
        avio_wb32(pb, 0xA2805140);
    }

    if (par->channels > 2 && par->channel_layout) {
        ffio_wfourcc(pb, "CHAN");
        avio_wb32(pb, 12);
        ff_mov_write_chan(pb, par->channel_layout);
    }

    put_meta(s, "title",     MKTAG('N', 'A', 'M', 'E'));
    put_meta(s, "author",    MKTAG('A', 'U', 'T', 'H'));
    put_meta(s, "copyright", MKTAG('(', 'c', ')', ' '));
    put_meta(s, "comment",   MKTAG('A', 'N', 'N', 'O'));

    /* Common chunk */
    ffio_wfourcc(pb, "COMM");
    avio_wb32(pb, aifc ? 24 : 18); /* size */
    avio_wb16(pb, par->channels);  /* Number of channels */

    aiff->frames = avio_tell(pb);
    avio_wb32(pb, 0);              /* Number of frames */

    if (!par->bits_per_coded_sample)
        par->bits_per_coded_sample = av_get_bits_per_sample(par->codec_id);
    if (!par->bits_per_coded_sample) {
        av_log(s, AV_LOG_ERROR, "could not compute bits per sample\n");
        return AVERROR(EINVAL);
    }
    if (!par->block_align)
        par->block_align = (par->bits_per_coded_sample * par->channels) >> 3;

    avio_wb16(pb, par->bits_per_coded_sample); /* Sample size */

    sample_rate = av_double2int(par->sample_rate);
    avio_wb16(pb, (sample_rate >> 52) + (16383 - 1023));
    avio_wb64(pb, UINT64_C(1) << 63 | sample_rate << 11);

    if (aifc) {
        avio_wl32(pb, par->codec_tag);
        avio_wb16(pb, 0);
    }

    if (  (par->codec_tag == MKTAG('Q','D','M','2')
        || par->codec_tag == MKTAG('Q','c','l','p')) && par->extradata_size) {
        ffio_wfourcc(pb, "wave");
        avio_wb32(pb, par->extradata_size);
        avio_write(pb, par->extradata, par->extradata_size);
    }

    /* Sound data chunk */
    ffio_wfourcc(pb, "SSND");
    aiff->ssnd = avio_tell(pb);         /* Sound chunk size */
    avio_wb32(pb, 0);                    /* Sound samples data size */
    avio_wb32(pb, 0);                    /* Data offset */
    avio_wb32(pb, 0);                    /* Block-size (block align) */

    avpriv_set_pts_info(s->streams[aiff->audio_stream_idx], 64, 1,
                        s->streams[aiff->audio_stream_idx]->codecpar->sample_rate);

    /* Data is starting here */
    avio_flush(pb);

    return 0;
}