#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ codec_type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  channels; int /*<<< orphan*/  bits_per_coded_sample; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_13__ {char* key; char* value; } ;
struct TYPE_12__ {int nb_streams; TYPE_1__** streams; int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; } ;
struct TYPE_11__ {TYPE_4__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVDictionaryEntry ;
typedef  TYPE_4__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int SMJPEG_HEND ; 
 char* SMJPEG_MAGIC ; 
 int SMJPEG_SND ; 
 int SMJPEG_TXT ; 
 int SMJPEG_VID ; 
 TYPE_3__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int) ; 
 int ff_codec_get_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_codec_smjpeg_audio_tags ; 
 int /*<<< orphan*/  ff_codec_smjpeg_video_tags ; 
 int /*<<< orphan*/  ff_standardize_creation_time (TYPE_2__*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int smjpeg_write_header(AVFormatContext *s)
{
    AVDictionaryEntry *t = NULL;
    AVIOContext *pb = s->pb;
    int n, tag;

    if (s->nb_streams > 2) {
        av_log(s, AV_LOG_ERROR, "more than >2 streams are not supported\n");
        return AVERROR(EINVAL);
    }
    avio_write(pb, SMJPEG_MAGIC, 8);
    avio_wb32(pb, 0);
    avio_wb32(pb, 0);

    ff_standardize_creation_time(s);
    while ((t = av_dict_get(s->metadata, "", t, AV_DICT_IGNORE_SUFFIX))) {
        avio_wl32(pb, SMJPEG_TXT);
        avio_wb32(pb, strlen(t->key) + strlen(t->value) + 3);
        avio_write(pb, t->key, strlen(t->key));
        avio_write(pb, " = ", 3);
        avio_write(pb, t->value, strlen(t->value));
    }

    for (n = 0; n < s->nb_streams; n++) {
        AVStream *st = s->streams[n];
        AVCodecParameters *par = st->codecpar;
        if (par->codec_type == AVMEDIA_TYPE_AUDIO) {
            tag = ff_codec_get_tag(ff_codec_smjpeg_audio_tags, par->codec_id);
            if (!tag) {
                av_log(s, AV_LOG_ERROR, "unsupported audio codec\n");
                return AVERROR(EINVAL);
            }
            avio_wl32(pb, SMJPEG_SND);
            avio_wb32(pb, 8);
            avio_wb16(pb, par->sample_rate);
            avio_w8(pb, par->bits_per_coded_sample);
            avio_w8(pb, par->channels);
            avio_wl32(pb, tag);
            avpriv_set_pts_info(st, 32, 1, 1000);
        } else if (par->codec_type == AVMEDIA_TYPE_VIDEO) {
            tag = ff_codec_get_tag(ff_codec_smjpeg_video_tags, par->codec_id);
            if (!tag) {
                av_log(s, AV_LOG_ERROR, "unsupported video codec\n");
                return AVERROR(EINVAL);
            }
            avio_wl32(pb, SMJPEG_VID);
            avio_wb32(pb, 12);
            avio_wb32(pb, 0);
            avio_wb16(pb, par->width);
            avio_wb16(pb, par->height);
            avio_wl32(pb, tag);
            avpriv_set_pts_info(st, 32, 1, 1000);
        }
    }

    avio_wl32(pb, SMJPEG_HEND);
    avio_flush(pb);

    return 0;
}