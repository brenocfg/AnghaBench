#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* codecpar; } ;
struct TYPE_4__ {int channels; int sample_rate; int bit_rate; int block_align; int bits_per_coded_sample; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_5POINT1 ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S24DAUD ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MKTAG (char,char,unsigned char,char) ; 
 TYPE_2__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int daud_header(AVFormatContext *s) {
    AVStream *st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id = AV_CODEC_ID_PCM_S24DAUD;
    st->codecpar->codec_tag = MKTAG('d', 'a', 'u', 'd');
    st->codecpar->channels = 6;
    st->codecpar->channel_layout = AV_CH_LAYOUT_5POINT1;
    st->codecpar->sample_rate = 96000;
    st->codecpar->bit_rate = 3 * 6 * 96000 * 8;
    st->codecpar->block_align = 3 * 6;
    st->codecpar->bits_per_coded_sample = 24;
    return 0;
}