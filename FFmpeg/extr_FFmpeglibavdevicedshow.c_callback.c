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
typedef  int /*<<< orphan*/  uint8_t ;
struct dshow_ctx {int* curbufsize; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * event; TYPE_1__* pktl; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  enum dshowDeviceType { ____Placeholder_dshowDeviceType } dshowDeviceType ;
struct TYPE_9__ {int stream_index; int /*<<< orphan*/  data; int /*<<< orphan*/  pts; } ;
struct TYPE_8__ {struct dshow_ctx* priv_data; } ;
struct TYPE_7__ {struct TYPE_7__* next; TYPE_4__ pkt; } ;
typedef  TYPE_1__ AVPacketList ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 TYPE_1__* av_mallocz (int) ; 
 scalar_t__ av_new_packet (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ shall_we_drop (TYPE_2__*,int,int) ; 

__attribute__((used)) static void
callback(void *priv_data, int index, uint8_t *buf, int buf_size, int64_t time, enum dshowDeviceType devtype)
{
    AVFormatContext *s = priv_data;
    struct dshow_ctx *ctx = s->priv_data;
    AVPacketList **ppktl, *pktl_next;

//    dump_videohdr(s, vdhdr);

    WaitForSingleObject(ctx->mutex, INFINITE);

    if(shall_we_drop(s, index, devtype))
        goto fail;

    pktl_next = av_mallocz(sizeof(AVPacketList));
    if(!pktl_next)
        goto fail;

    if(av_new_packet(&pktl_next->pkt, buf_size) < 0) {
        av_free(pktl_next);
        goto fail;
    }

    pktl_next->pkt.stream_index = index;
    pktl_next->pkt.pts = time;
    memcpy(pktl_next->pkt.data, buf, buf_size);

    for(ppktl = &ctx->pktl ; *ppktl ; ppktl = &(*ppktl)->next);
    *ppktl = pktl_next;
    ctx->curbufsize[index] += buf_size;

    SetEvent(ctx->event[1]);
    ReleaseMutex(ctx->mutex);

    return;
fail:
    ReleaseMutex(ctx->mutex);
    return;
}