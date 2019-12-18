#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct dshow_ctx {scalar_t__ video_codec_id; scalar_t__ pixel_format; int /*<<< orphan*/ * event; int /*<<< orphan*/ * media_event; int /*<<< orphan*/ * control; int /*<<< orphan*/  mutex; scalar_t__* curbufsize; scalar_t__ list_options; scalar_t__* device_name; scalar_t__ list_devices; int /*<<< orphan*/ * graph; scalar_t__ framerate; int /*<<< orphan*/  requested_framerate; } ;
struct TYPE_10__ {scalar_t__ video_codec_id; struct dshow_ctx* priv_data; } ;
typedef  int /*<<< orphan*/  OAFilterState ;
typedef  int /*<<< orphan*/  IMediaEvent ;
typedef  int /*<<< orphan*/  IMediaControl ;
typedef  int /*<<< orphan*/  IGraphBuilder ;
typedef  int /*<<< orphan*/  ICreateDevEnum ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXIT ; 
 scalar_t__ AV_CODEC_ID_RAWVIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 size_t AudioDevice ; 
 int /*<<< orphan*/  AudioSourceDevice ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_FilterGraph ; 
 int /*<<< orphan*/  CLSID_SystemDeviceEnum ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEvent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateMutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DUPLICATE_SAME_ACCESS ; 
 int DuplicateHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  ICreateDevEnum_Release (int /*<<< orphan*/ *) ; 
 int IGraphBuilder_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_ICreateDevEnum ; 
 int /*<<< orphan*/  IID_IGraphBuilder ; 
 int /*<<< orphan*/  IID_IMediaControl ; 
 int /*<<< orphan*/  IID_IMediaEvent ; 
 int IMediaControl_GetState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IMediaControl_Run (int /*<<< orphan*/ *) ; 
 int IMediaEvent_GetEventHandle (int /*<<< orphan*/ *,void*) ; 
 int S_FALSE ; 
 int S_OK ; 
 size_t VideoDevice ; 
 int /*<<< orphan*/  VideoSourceDevice ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_parse_video_rate (int /*<<< orphan*/ *,scalar_t__) ; 
 int dshow_add_device (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  dshow_cycle_devices (TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dshow_list_device_options (TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int dshow_open_device (TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dshow_read_close (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_device_name (TYPE_1__*) ; 

__attribute__((used)) static int dshow_read_header(AVFormatContext *avctx)
{
    struct dshow_ctx *ctx = avctx->priv_data;
    IGraphBuilder *graph = NULL;
    ICreateDevEnum *devenum = NULL;
    IMediaControl *control = NULL;
    IMediaEvent *media_event = NULL;
    HANDLE media_event_handle;
    HANDLE proc;
    int ret = AVERROR(EIO);
    int r;

    CoInitialize(0);

    if (!ctx->list_devices && !parse_device_name(avctx)) {
        av_log(avctx, AV_LOG_ERROR, "Malformed dshow input string.\n");
        goto error;
    }

    ctx->video_codec_id = avctx->video_codec_id ? avctx->video_codec_id
                                                : AV_CODEC_ID_RAWVIDEO;
    if (ctx->pixel_format != AV_PIX_FMT_NONE) {
        if (ctx->video_codec_id != AV_CODEC_ID_RAWVIDEO) {
            av_log(avctx, AV_LOG_ERROR, "Pixel format may only be set when "
                              "video codec is not set or set to rawvideo\n");
            ret = AVERROR(EINVAL);
            goto error;
        }
    }
    if (ctx->framerate) {
        r = av_parse_video_rate(&ctx->requested_framerate, ctx->framerate);
        if (r < 0) {
            av_log(avctx, AV_LOG_ERROR, "Could not parse framerate '%s'.\n", ctx->framerate);
            goto error;
        }
    }

    r = CoCreateInstance(&CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
                         &IID_IGraphBuilder, (void **) &graph);
    if (r != S_OK) {
        av_log(avctx, AV_LOG_ERROR, "Could not create capture graph.\n");
        goto error;
    }
    ctx->graph = graph;

    r = CoCreateInstance(&CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                         &IID_ICreateDevEnum, (void **) &devenum);
    if (r != S_OK) {
        av_log(avctx, AV_LOG_ERROR, "Could not enumerate system devices.\n");
        goto error;
    }

    if (ctx->list_devices) {
        av_log(avctx, AV_LOG_INFO, "DirectShow video devices (some may be both video and audio devices)\n");
        dshow_cycle_devices(avctx, devenum, VideoDevice, VideoSourceDevice, NULL, NULL);
        av_log(avctx, AV_LOG_INFO, "DirectShow audio devices\n");
        dshow_cycle_devices(avctx, devenum, AudioDevice, AudioSourceDevice, NULL, NULL);
        ret = AVERROR_EXIT;
        goto error;
    }
    if (ctx->list_options) {
        if (ctx->device_name[VideoDevice])
            if ((r = dshow_list_device_options(avctx, devenum, VideoDevice, VideoSourceDevice))) {
                ret = r;
                goto error;
            }
        if (ctx->device_name[AudioDevice]) {
            if (dshow_list_device_options(avctx, devenum, AudioDevice, AudioSourceDevice)) {
                /* show audio options from combined video+audio sources as fallback */
                if ((r = dshow_list_device_options(avctx, devenum, AudioDevice, VideoSourceDevice))) {
                    ret = r;
                    goto error;
                }
            }
        }
    }
    if (ctx->device_name[VideoDevice]) {
        if ((r = dshow_open_device(avctx, devenum, VideoDevice, VideoSourceDevice)) < 0 ||
            (r = dshow_add_device(avctx, VideoDevice)) < 0) {
            ret = r;
            goto error;
        }
    }
    if (ctx->device_name[AudioDevice]) {
        if ((r = dshow_open_device(avctx, devenum, AudioDevice, AudioSourceDevice)) < 0 ||
            (r = dshow_add_device(avctx, AudioDevice)) < 0) {
            av_log(avctx, AV_LOG_INFO, "Searching for audio device within video devices for %s\n", ctx->device_name[AudioDevice]);
            /* see if there's a video source with an audio pin with the given audio name */
            if ((r = dshow_open_device(avctx, devenum, AudioDevice, VideoSourceDevice)) < 0 ||
                (r = dshow_add_device(avctx, AudioDevice)) < 0) {
                ret = r;
                goto error;
            }
        }
    }
    if (ctx->list_options) {
        /* allow it to list crossbar options in dshow_open_device */
        ret = AVERROR_EXIT;
        goto error;
    }
    ctx->curbufsize[0] = 0;
    ctx->curbufsize[1] = 0;
    ctx->mutex = CreateMutex(NULL, 0, NULL);
    if (!ctx->mutex) {
        av_log(avctx, AV_LOG_ERROR, "Could not create Mutex\n");
        goto error;
    }
    ctx->event[1] = CreateEvent(NULL, 1, 0, NULL);
    if (!ctx->event[1]) {
        av_log(avctx, AV_LOG_ERROR, "Could not create Event\n");
        goto error;
    }

    r = IGraphBuilder_QueryInterface(graph, &IID_IMediaControl, (void **) &control);
    if (r != S_OK) {
        av_log(avctx, AV_LOG_ERROR, "Could not get media control.\n");
        goto error;
    }
    ctx->control = control;

    r = IGraphBuilder_QueryInterface(graph, &IID_IMediaEvent, (void **) &media_event);
    if (r != S_OK) {
        av_log(avctx, AV_LOG_ERROR, "Could not get media event.\n");
        goto error;
    }
    ctx->media_event = media_event;

    r = IMediaEvent_GetEventHandle(media_event, (void *) &media_event_handle);
    if (r != S_OK) {
        av_log(avctx, AV_LOG_ERROR, "Could not get media event handle.\n");
        goto error;
    }
    proc = GetCurrentProcess();
    r = DuplicateHandle(proc, media_event_handle, proc, &ctx->event[0],
                        0, 0, DUPLICATE_SAME_ACCESS);
    if (!r) {
        av_log(avctx, AV_LOG_ERROR, "Could not duplicate media event handle.\n");
        goto error;
    }

    r = IMediaControl_Run(control);
    if (r == S_FALSE) {
        OAFilterState pfs;
        r = IMediaControl_GetState(control, 0, &pfs);
    }
    if (r != S_OK) {
        av_log(avctx, AV_LOG_ERROR, "Could not run graph (sometimes caused by a device already in use by other application)\n");
        goto error;
    }

    ret = 0;

error:

    if (devenum)
        ICreateDevEnum_Release(devenum);

    if (ret < 0)
        dshow_read_close(avctx);

    return ret;
}