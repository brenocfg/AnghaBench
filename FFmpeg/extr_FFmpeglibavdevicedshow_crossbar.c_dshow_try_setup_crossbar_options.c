#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dshow_ctx {scalar_t__ show_analog_tv_tuner_audio_dialog; scalar_t__ show_analog_tv_tuner_dialog; scalar_t__ show_audio_crossbar_connection_dialog; scalar_t__ show_video_crossbar_connection_dialog; } ;
typedef  enum dshowDeviceType { ____Placeholder_dshowDeviceType } dshowDeviceType ;
struct TYPE_6__ {struct dshow_ctx* priv_data; } ;
typedef  int /*<<< orphan*/  ICaptureGraphBuilder2 ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  int /*<<< orphan*/  IAMTVTuner ;
typedef  int /*<<< orphan*/  IAMCrossbar ;
typedef  int /*<<< orphan*/  IAMAudioInputMixer ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AudioDevice ; 
 scalar_t__ IAMCrossbar_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAMCrossbar_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAMTVTuner_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ICaptureGraphBuilder2_FindInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IAMCrossbar ; 
 int /*<<< orphan*/  IID_IAMTVAudio ; 
 int /*<<< orphan*/  IID_IAMTVTuner ; 
 int /*<<< orphan*/  IID_IBaseFilter ; 
 int /*<<< orphan*/  LOOK_UPSTREAM_ONLY ; 
 scalar_t__ S_OK ; 
 int VideoDevice ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dshow_show_filter_properties (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ setup_crossbar_options (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

HRESULT
dshow_try_setup_crossbar_options(ICaptureGraphBuilder2 *graph_builder2,
    IBaseFilter *device_filter, enum dshowDeviceType devtype, AVFormatContext *avctx)
{
    struct dshow_ctx *ctx = avctx->priv_data;
    IAMCrossbar *cross_bar = NULL;
    IBaseFilter *cross_bar_base_filter = NULL;
    IAMTVTuner *tv_tuner_filter = NULL;
    IBaseFilter *tv_tuner_base_filter = NULL;
    IAMAudioInputMixer *tv_audio_filter = NULL;
    IBaseFilter *tv_audio_base_filter = NULL;
    HRESULT hr;

    hr = ICaptureGraphBuilder2_FindInterface(graph_builder2, &LOOK_UPSTREAM_ONLY, (const GUID *) NULL,
            device_filter, &IID_IAMCrossbar, (void**) &cross_bar);
    if (hr != S_OK) {
        /* no crossbar found */
        hr = S_OK;
        goto end;
    }
    /* TODO some TV tuners apparently have multiple crossbars? */

    if (devtype == VideoDevice && ctx->show_video_crossbar_connection_dialog ||
        devtype == AudioDevice && ctx->show_audio_crossbar_connection_dialog) {
        hr = IAMCrossbar_QueryInterface(cross_bar, &IID_IBaseFilter, (void **) &cross_bar_base_filter);
        if (hr != S_OK)
            goto end;
        dshow_show_filter_properties(cross_bar_base_filter, avctx);
    }

    if (devtype == VideoDevice && ctx->show_analog_tv_tuner_dialog) {
        hr = ICaptureGraphBuilder2_FindInterface(graph_builder2, &LOOK_UPSTREAM_ONLY, NULL,
             device_filter, &IID_IAMTVTuner, (void**) &tv_tuner_filter);
        if (hr == S_OK) {
            hr = IAMCrossbar_QueryInterface(tv_tuner_filter, &IID_IBaseFilter, (void **) &tv_tuner_base_filter);
            if (hr != S_OK)
                goto end;
            dshow_show_filter_properties(tv_tuner_base_filter, avctx);
        } else {
            av_log(avctx, AV_LOG_WARNING, "unable to find a tv tuner to display dialog for!");
        }
    }
    if (devtype == AudioDevice && ctx->show_analog_tv_tuner_audio_dialog) {
        hr = ICaptureGraphBuilder2_FindInterface(graph_builder2, &LOOK_UPSTREAM_ONLY, NULL,
             device_filter, &IID_IAMTVAudio, (void**) &tv_audio_filter);
        if (hr == S_OK) {
            hr = IAMCrossbar_QueryInterface(tv_audio_filter, &IID_IBaseFilter, (void **) &tv_audio_base_filter);
            if (hr != S_OK)
                goto end;
            dshow_show_filter_properties(tv_audio_base_filter, avctx);
        } else {
            av_log(avctx, AV_LOG_WARNING, "unable to find a tv audio tuner to display dialog for!");
        }
    }

    hr = setup_crossbar_options(cross_bar, devtype, avctx);
    if (hr != S_OK)
        goto end;

end:
    if (cross_bar)
        IAMCrossbar_Release(cross_bar);
    if (cross_bar_base_filter)
        IBaseFilter_Release(cross_bar_base_filter);
    if (tv_tuner_filter)
        IAMTVTuner_Release(tv_tuner_filter);
    if (tv_tuner_base_filter)
        IBaseFilter_Release(tv_tuner_base_filter);
    return hr;
}