#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dshow_ctx {TYPE_1__* pktl; scalar_t__* event; scalar_t__ mutex; int /*<<< orphan*/ * device_unique_name; int /*<<< orphan*/ * device_name; int /*<<< orphan*/ ** device_filter; scalar_t__* device_pin; scalar_t__* capture_filter; scalar_t__* capture_pin; scalar_t__ graph; scalar_t__ media_event; scalar_t__ control; } ;
struct TYPE_6__ {struct dshow_ctx* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  pkt; struct TYPE_5__* next; } ;
typedef  int /*<<< orphan*/  IEnumFilters ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  TYPE_1__ AVPacketList ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 size_t AudioDevice ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ *) ; 
 int IEnumFilters_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumFilters_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumFilters_Reset (int /*<<< orphan*/ *) ; 
 int IGraphBuilder_EnumFilters (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IGraphBuilder_Release (scalar_t__) ; 
 int IGraphBuilder_RemoveFilter (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaControl_Release (scalar_t__) ; 
 int /*<<< orphan*/  IMediaControl_Stop (scalar_t__) ; 
 int /*<<< orphan*/  IMediaEvent_Release (scalar_t__) ; 
 int /*<<< orphan*/  IPin_Release (scalar_t__) ; 
 int S_OK ; 
 size_t VideoDevice ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libAVFilter_Release (scalar_t__) ; 
 int /*<<< orphan*/  libAVPin_Release (scalar_t__) ; 

__attribute__((used)) static int
dshow_read_close(AVFormatContext *s)
{
    struct dshow_ctx *ctx = s->priv_data;
    AVPacketList *pktl;

    if (ctx->control) {
        IMediaControl_Stop(ctx->control);
        IMediaControl_Release(ctx->control);
    }

    if (ctx->media_event)
        IMediaEvent_Release(ctx->media_event);

    if (ctx->graph) {
        IEnumFilters *fenum;
        int r;
        r = IGraphBuilder_EnumFilters(ctx->graph, &fenum);
        if (r == S_OK) {
            IBaseFilter *f;
            IEnumFilters_Reset(fenum);
            while (IEnumFilters_Next(fenum, 1, &f, NULL) == S_OK) {
                if (IGraphBuilder_RemoveFilter(ctx->graph, f) == S_OK)
                    IEnumFilters_Reset(fenum); /* When a filter is removed,
                                                * the list must be reset. */
                IBaseFilter_Release(f);
            }
            IEnumFilters_Release(fenum);
        }
        IGraphBuilder_Release(ctx->graph);
    }

    if (ctx->capture_pin[VideoDevice])
        libAVPin_Release(ctx->capture_pin[VideoDevice]);
    if (ctx->capture_pin[AudioDevice])
        libAVPin_Release(ctx->capture_pin[AudioDevice]);
    if (ctx->capture_filter[VideoDevice])
        libAVFilter_Release(ctx->capture_filter[VideoDevice]);
    if (ctx->capture_filter[AudioDevice])
        libAVFilter_Release(ctx->capture_filter[AudioDevice]);

    if (ctx->device_pin[VideoDevice])
        IPin_Release(ctx->device_pin[VideoDevice]);
    if (ctx->device_pin[AudioDevice])
        IPin_Release(ctx->device_pin[AudioDevice]);
    if (ctx->device_filter[VideoDevice])
        IBaseFilter_Release(ctx->device_filter[VideoDevice]);
    if (ctx->device_filter[AudioDevice])
        IBaseFilter_Release(ctx->device_filter[AudioDevice]);

    av_freep(&ctx->device_name[0]);
    av_freep(&ctx->device_name[1]);
    av_freep(&ctx->device_unique_name[0]);
    av_freep(&ctx->device_unique_name[1]);

    if(ctx->mutex)
        CloseHandle(ctx->mutex);
    if(ctx->event[0])
        CloseHandle(ctx->event[0]);
    if(ctx->event[1])
        CloseHandle(ctx->event[1]);

    pktl = ctx->pktl;
    while (pktl) {
        AVPacketList *next = pktl->next;
        av_packet_unref(&pktl->pkt);
        av_free(pktl);
        pktl = next;
    }

    CoUninitialize();

    return 0;
}