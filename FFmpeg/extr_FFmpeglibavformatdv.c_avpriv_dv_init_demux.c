#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ start_time; TYPE_1__* codecpar; } ;
struct TYPE_8__ {TYPE_4__* vst; int /*<<< orphan*/ * fctx; } ;
struct TYPE_7__ {int bit_rate; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ DVDemuxContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_DVVIDEO ; 
 int /*<<< orphan*/  av_free (TYPE_2__*) ; 
 TYPE_2__* av_mallocz (int) ; 
 TYPE_4__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DVDemuxContext *avpriv_dv_init_demux(AVFormatContext *s)
{
    DVDemuxContext *c;

    c = av_mallocz(sizeof(DVDemuxContext));
    if (!c)
        return NULL;

    c->vst = avformat_new_stream(s, NULL);
    if (!c->vst) {
        av_free(c);
        return NULL;
    }

    c->fctx                   = s;
    c->vst->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    c->vst->codecpar->codec_id   = AV_CODEC_ID_DVVIDEO;
    c->vst->codecpar->bit_rate   = 25000000;
    c->vst->start_time        = 0;

    return c;
}