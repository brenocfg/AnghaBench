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
struct dshow_ctx {int eof; int /*<<< orphan*/ * event; int /*<<< orphan*/  media_event; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * curbufsize; TYPE_1__* pktl; } ;
struct TYPE_9__ {int flags; struct dshow_ctx* priv_data; } ;
struct TYPE_8__ {size_t stream_index; int size; } ;
struct TYPE_7__ {struct TYPE_7__* next; TYPE_2__ pkt; } ;
typedef  TYPE_1__ AVPacketList ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVFMT_FLAG_NONBLOCK ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForMultipleObjects (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 scalar_t__ dshow_check_event_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dshow_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    struct dshow_ctx *ctx = s->priv_data;
    AVPacketList *pktl = NULL;

    while (!ctx->eof && !pktl) {
        WaitForSingleObject(ctx->mutex, INFINITE);
        pktl = ctx->pktl;
        if (pktl) {
            *pkt = pktl->pkt;
            ctx->pktl = ctx->pktl->next;
            av_free(pktl);
            ctx->curbufsize[pkt->stream_index] -= pkt->size;
        }
        ResetEvent(ctx->event[1]);
        ReleaseMutex(ctx->mutex);
        if (!pktl) {
            if (dshow_check_event_queue(ctx->media_event) < 0) {
                ctx->eof = 1;
            } else if (s->flags & AVFMT_FLAG_NONBLOCK) {
                return AVERROR(EAGAIN);
            } else {
                WaitForMultipleObjects(2, ctx->event, 0, INFINITE);
            }
        }
    }

    return ctx->eof ? AVERROR(EIO) : pkt->size;
}