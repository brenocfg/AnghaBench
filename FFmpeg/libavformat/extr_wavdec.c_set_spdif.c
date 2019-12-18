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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_10__ {int spdif; } ;
typedef  TYPE_3__ WAVDemuxContext ;
struct TYPE_11__ {int /*<<< orphan*/  pb; TYPE_2__** streams; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {int codec_tag; int codec_id; } ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVPROBE_SCORE_EXTENSION ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ CONFIG_SPDIF_DEMUXER ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int avio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 int ff_spdif_probe (int /*<<< orphan*/ *,int,int*) ; 
 int ffio_ensure_seekback (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_spdif(AVFormatContext *s, WAVDemuxContext *wav)
{
    if (CONFIG_SPDIF_DEMUXER && s->streams[0]->codecpar->codec_tag == 1) {
        enum AVCodecID codec;
        int len = 1<<16;
        int ret = ffio_ensure_seekback(s->pb, len);

        if (ret >= 0) {
            uint8_t *buf = av_malloc(len);
            if (!buf) {
                ret = AVERROR(ENOMEM);
            } else {
                int64_t pos = avio_tell(s->pb);
                len = ret = avio_read(s->pb, buf, len);
                if (len >= 0) {
                    ret = ff_spdif_probe(buf, len, &codec);
                    if (ret > AVPROBE_SCORE_EXTENSION) {
                        s->streams[0]->codecpar->codec_id = codec;
                        wav->spdif = 1;
                    }
                }
                avio_seek(s->pb, pos, SEEK_SET);
                av_free(buf);
            }
        }

        if (ret < 0)
            av_log(s, AV_LOG_WARNING, "Cannot check for SPDIF\n");
    }
}