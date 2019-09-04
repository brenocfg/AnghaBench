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
struct TYPE_12__ {TYPE_2__* priv_data; } ;
struct TYPE_11__ {TYPE_1__* codecpar; } ;
struct TYPE_10__ {int get_next; scalar_t__ audio_pos; } ;
struct TYPE_9__ {int width; int height; int channels; int sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ BMVContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CODEC_ID_BMV_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_BMV_VIDEO ; 
 int /*<<< orphan*/  AV_PIX_FMT_PAL8 ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 

__attribute__((used)) static int bmv_read_header(AVFormatContext *s)
{
    AVStream *st, *ast;
    BMVContext *c = s->priv_data;

    st = avformat_new_stream(s, 0);
    if (!st)
        return AVERROR(ENOMEM);
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id   = AV_CODEC_ID_BMV_VIDEO;
    st->codecpar->width      = 640;
    st->codecpar->height     = 429;
    st->codecpar->format     = AV_PIX_FMT_PAL8;
    avpriv_set_pts_info(st, 16, 1, 12);
    ast = avformat_new_stream(s, 0);
    if (!ast)
        return AVERROR(ENOMEM);
    ast->codecpar->codec_type      = AVMEDIA_TYPE_AUDIO;
    ast->codecpar->codec_id        = AV_CODEC_ID_BMV_AUDIO;
    ast->codecpar->channels        = 2;
    ast->codecpar->channel_layout  = AV_CH_LAYOUT_STEREO;
    ast->codecpar->sample_rate     = 22050;
    avpriv_set_pts_info(ast, 16, 1, 22050);

    c->get_next  = 1;
    c->audio_pos = 0;
    return 0;
}