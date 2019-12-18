#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int nb_streams; TYPE_5__** streams; TYPE_4__* priv_data; } ;
struct TYPE_14__ {TYPE_2__* priv_data; TYPE_1__* codecpar; } ;
struct TYPE_13__ {TYPE_3__* page_list; } ;
struct TYPE_12__ {struct TYPE_12__* next; } ;
struct TYPE_11__ {struct TYPE_11__** header; } ;
struct TYPE_10__ {scalar_t__ codec_id; } ;
typedef  TYPE_2__ OGGStreamContext ;
typedef  TYPE_3__ OGGPageList ;
typedef  TYPE_4__ OGGContext ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_FLAC ; 
 scalar_t__ AV_CODEC_ID_OPUS ; 
 scalar_t__ AV_CODEC_ID_SPEEX ; 
 scalar_t__ AV_CODEC_ID_VP8 ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 

__attribute__((used)) static void ogg_free(AVFormatContext *s)
{
    OGGContext *ogg = s->priv_data;
    OGGPageList *p = ogg->page_list;
    int i;

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        OGGStreamContext *oggstream = st->priv_data;
        if (!oggstream)
            continue;
        if (st->codecpar->codec_id == AV_CODEC_ID_FLAC ||
            st->codecpar->codec_id == AV_CODEC_ID_SPEEX ||
            st->codecpar->codec_id == AV_CODEC_ID_OPUS ||
            st->codecpar->codec_id == AV_CODEC_ID_VP8) {
            av_freep(&oggstream->header[0]);
        }
        av_freep(&oggstream->header[1]);
        av_freep(&st->priv_data);
    }

    while (p) {
        OGGPageList *next = p->next;
        av_free(p);
        p = next;
    }
    ogg->page_list = NULL;
}