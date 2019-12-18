#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ codec_id; size_t channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_12__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {int /*<<< orphan*/  metadata; TYPE_1__** streams; int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_10__ {size_t header_size; } ;
struct TYPE_9__ {TYPE_5__* codecpar; } ;
typedef  TYPE_2__ SoXContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVDictionaryEntry ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_CODEC_ID_PCM_S32BE ; 
 scalar_t__ AV_CODEC_ID_PCM_S32LE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 size_t FFALIGN (size_t,int) ; 
 size_t SOX_FIXED_HDR ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_double2int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ffio_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sox_write_header(AVFormatContext *s)
{
    SoXContext *sox = s->priv_data;
    AVIOContext *pb = s->pb;
    AVCodecParameters *par = s->streams[0]->codecpar;
    AVDictionaryEntry *comment;
    size_t comment_len = 0, comment_size;

    comment = av_dict_get(s->metadata, "comment", NULL, 0);
    if (comment)
        comment_len = strlen(comment->value);
    comment_size = FFALIGN(comment_len, 8);

    sox->header_size = SOX_FIXED_HDR + comment_size;

    if (par->codec_id == AV_CODEC_ID_PCM_S32LE) {
        ffio_wfourcc(pb, ".SoX");
        avio_wl32(pb, sox->header_size);
        avio_wl64(pb, 0); /* number of samples */
        avio_wl64(pb, av_double2int(par->sample_rate));
        avio_wl32(pb, par->channels);
        avio_wl32(pb, comment_size);
    } else if (par->codec_id == AV_CODEC_ID_PCM_S32BE) {
        ffio_wfourcc(pb, "XoS.");
        avio_wb32(pb, sox->header_size);
        avio_wb64(pb, 0); /* number of samples */
        avio_wb64(pb, av_double2int(par->sample_rate));
        avio_wb32(pb, par->channels);
        avio_wb32(pb, comment_size);
    } else {
        av_log(s, AV_LOG_ERROR, "invalid codec; use pcm_s32le or pcm_s32be\n");
        return AVERROR(EINVAL);
    }

    if (comment_len)
        avio_write(pb, comment->value, comment_len);

    ffio_fill(pb, 0, comment_size - comment_len);

    avio_flush(pb);

    return 0;
}