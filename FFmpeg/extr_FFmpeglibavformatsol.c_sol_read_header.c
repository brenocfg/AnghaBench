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
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_10__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {unsigned int codec_tag; int codec_id; unsigned int channels; unsigned int sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int AV_CODEC_ID_SOL_DPCM ; 
 unsigned int MKTAG (char,char,char,int /*<<< orphan*/ ) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 unsigned int avio_r8 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rl16 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,unsigned int) ; 
 unsigned int sol_channels (unsigned int,unsigned int) ; 
 int sol_codec_id (unsigned int,unsigned int) ; 
 unsigned int sol_codec_type (unsigned int,unsigned int) ; 

__attribute__((used)) static int sol_read_header(AVFormatContext *s)
{
    unsigned int magic,tag;
    AVIOContext *pb = s->pb;
    unsigned int id, channels, rate, type;
    enum AVCodecID codec;
    AVStream *st;

    /* check ".snd" header */
    magic = avio_rl16(pb);
    tag = avio_rl32(pb);
    if (tag != MKTAG('S', 'O', 'L', 0))
        return -1;
    rate = avio_rl16(pb);
    type = avio_r8(pb);
    avio_skip(pb, 4); /* size */
    if (magic != 0x0B8D)
        avio_r8(pb); /* newer SOLs contain padding byte */

    codec = sol_codec_id(magic, type);
    channels = sol_channels(magic, type);

    if (codec == AV_CODEC_ID_SOL_DPCM)
        id = sol_codec_type(magic, type);
    else id = 0;

    /* now we are ready: build format streams */
    st = avformat_new_stream(s, NULL);
    if (!st)
        return -1;
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_tag = id;
    st->codecpar->codec_id = codec;
    st->codecpar->channels = channels;
    st->codecpar->channel_layout = channels == 1 ? AV_CH_LAYOUT_MONO :
                                                   AV_CH_LAYOUT_STEREO;
    st->codecpar->sample_rate = rate;
    avpriv_set_pts_info(st, 64, 1, rate);
    return 0;
}