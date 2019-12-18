#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {TYPE_5__** streams; TYPE_4__* priv_data; } ;
struct TYPE_17__ {TYPE_5__** streams; TYPE_1__* oformat; } ;
struct TYPE_16__ {size_t stream_index; } ;
struct TYPE_15__ {TYPE_2__* internal; } ;
struct TYPE_14__ {TYPE_3__* streams; } ;
struct TYPE_13__ {TYPE_7__* ctx; } ;
struct TYPE_12__ {scalar_t__ nb_bsfcs; int /*<<< orphan*/ * bsfcs; } ;
struct TYPE_11__ {int (* check_bitstream ) (TYPE_7__*,TYPE_6__*) ;} ;
typedef  TYPE_3__ OutputStream ;
typedef  TYPE_4__ DASHContext ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVPacket ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int stub1 (TYPE_7__*,TYPE_6__*) ; 

__attribute__((used)) static int dash_check_bitstream(struct AVFormatContext *s, const AVPacket *avpkt)
{
    DASHContext *c = s->priv_data;
    OutputStream *os = &c->streams[avpkt->stream_index];
    AVFormatContext *oc = os->ctx;
    if (oc->oformat->check_bitstream) {
        int ret;
        AVPacket pkt = *avpkt;
        pkt.stream_index = 0;
        ret = oc->oformat->check_bitstream(oc, &pkt);
        if (ret == 1) {
            AVStream *st = s->streams[avpkt->stream_index];
            AVStream *ost = oc->streams[0];
            st->internal->bsfcs = ost->internal->bsfcs;
            st->internal->nb_bsfcs = ost->internal->nb_bsfcs;
            ost->internal->bsfcs = NULL;
            ost->internal->nb_bsfcs = 0;
        }
        return ret;
    }
    return 1;
}