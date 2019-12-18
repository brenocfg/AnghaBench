#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ start_time; TYPE_1__* codecpar; } ;
struct TYPE_8__ {int /*<<< orphan*/  rate; } ;
struct TYPE_7__ {int channels; int bits_per_coded_sample; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ SIFFContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_U8 ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_audio_stream(AVFormatContext *s, SIFFContext *c)
{
    AVStream *ast;
    ast = avformat_new_stream(s, NULL);
    if (!ast)
        return AVERROR(ENOMEM);
    ast->codecpar->codec_type            = AVMEDIA_TYPE_AUDIO;
    ast->codecpar->codec_id              = AV_CODEC_ID_PCM_U8;
    ast->codecpar->channels              = 1;
    ast->codecpar->channel_layout        = AV_CH_LAYOUT_MONO;
    ast->codecpar->bits_per_coded_sample = 8;
    ast->codecpar->sample_rate           = c->rate;
    avpriv_set_pts_info(ast, 16, 1, c->rate);
    ast->start_time                   = 0;
    return 0;
}