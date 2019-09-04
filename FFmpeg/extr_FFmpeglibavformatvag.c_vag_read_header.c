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
struct TYPE_10__ {int /*<<< orphan*/  pb; } ;
struct TYPE_9__ {int duration; TYPE_1__* codecpar; } ;
struct TYPE_8__ {int channels; int sample_rate; int block_align; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_PSX ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ ) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 

__attribute__((used)) static int vag_read_header(AVFormatContext *s)
{
    AVStream *st;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    avio_skip(s->pb, 4);
    st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id    = AV_CODEC_ID_ADPCM_PSX;
    st->codecpar->channels    = 1 + (avio_rb32(s->pb) == 0x00000004);
    avio_skip(s->pb, 4);
    if (st->codecpar->channels > 1) {
        st->duration       = avio_rb32(s->pb);
    } else {
        st->duration       = avio_rb32(s->pb) / 16 * 28;
    }
    st->codecpar->sample_rate = avio_rb32(s->pb);
    if (st->codecpar->sample_rate <= 0)
        return AVERROR_INVALIDDATA;
    avio_seek(s->pb, 0x1000, SEEK_SET);
    if (avio_rl32(s->pb) == MKTAG('V','A','G','p')) {
        st->codecpar->block_align = 0x1000 * st->codecpar->channels;
        avio_seek(s->pb, 0, SEEK_SET);
        st->duration = st->duration / 16 * 28;
    } else {
        st->codecpar->block_align = 16 * st->codecpar->channels;
        avio_seek(s->pb, st->codecpar->channels > 1 ? 0x80 : 0x30, SEEK_SET);
    }
    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}