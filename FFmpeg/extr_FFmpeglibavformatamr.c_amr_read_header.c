#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {int sample_rate; int channels; int /*<<< orphan*/  codec_type; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; void* codec_tag; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AMRWB_header ; 
 int /*<<< orphan*/  AMR_header ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CODEC_ID_AMR_NB ; 
 int /*<<< orphan*/  AV_CODEC_ID_AMR_WB ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* MKTAG (char,char,char,char) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amr_read_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    AVStream *st;
    uint8_t header[9];

    avio_read(pb, header, 6);

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    if (memcmp(header, AMR_header, 6)) {
        avio_read(pb, header + 6, 3);
        if (memcmp(header, AMRWB_header, 9)) {
            return -1;
        }

        st->codecpar->codec_tag   = MKTAG('s', 'a', 'w', 'b');
        st->codecpar->codec_id    = AV_CODEC_ID_AMR_WB;
        st->codecpar->sample_rate = 16000;
    } else {
        st->codecpar->codec_tag   = MKTAG('s', 'a', 'm', 'r');
        st->codecpar->codec_id    = AV_CODEC_ID_AMR_NB;
        st->codecpar->sample_rate = 8000;
    }
    st->codecpar->channels   = 1;
    st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}