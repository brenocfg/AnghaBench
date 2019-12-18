#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  majortype; } ;
typedef  TYPE_1__ wchar_t ;
struct dshow_ctx {scalar_t__ pixel_format; scalar_t__ video_codec_id; int show_video_device_dialog; int show_audio_device_dialog; char* video_pin_name; char* audio_pin_name; char const* audio_buffer_size; scalar_t__ sample_rate; scalar_t__ channels; scalar_t__ requested_height; scalar_t__ requested_width; scalar_t__ framerate; } ;
typedef  enum dshowSourceFilterType { ____Placeholder_dshowSourceFilterType } dshowSourceFilterType ;
typedef  enum dshowDeviceType { ____Placeholder_dshowDeviceType } dshowDeviceType ;
struct TYPE_17__ {struct dshow_ctx* priv_data; } ;
struct TYPE_16__ {scalar_t__ dir; TYPE_1__* achName; int /*<<< orphan*/  pFilter; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ PIN_INFO ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IKsPropertySet ;
typedef  int /*<<< orphan*/  IEnumPins ;
typedef  int /*<<< orphan*/  IEnumMediaTypes ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_1__ AM_MEDIA_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  AMPROPERTY_PIN_CATEGORY ; 
 int /*<<< orphan*/  AMPROPSETID_Pin ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_CODEC_ID_RAWVIDEO ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 int AudioDevice ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_1__*) ; 
 int /*<<< orphan*/  EIO ; 
 int IBaseFilter_EnumPins (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ ) ; 
 int IEnumMediaTypes_Next (int /*<<< orphan*/ *,int,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumMediaTypes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumMediaTypes_Reset (int /*<<< orphan*/ *) ; 
 int IEnumPins_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumPins_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IKsPropertySet ; 
 int IKsPropertySet_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IKsPropertySet_Release (int /*<<< orphan*/ *) ; 
 int IPin_EnumMediaTypes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IPin_QueryId (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int IPin_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IPin_QueryPinInfo (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const MEDIATYPE_Audio ; 
 int /*<<< orphan*/  const MEDIATYPE_Video ; 
 scalar_t__ PINDIR_OUTPUT ; 
 int /*<<< orphan*/  const PIN_CATEGORY_CAPTURE ; 
 int S_OK ; 
 int VideoDevice ; 
 int VideoSourceDevice ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dshow_cycle_formats (TYPE_3__*,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ dshow_set_audio_buffer_size (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dshow_show_filter_properties (int /*<<< orphan*/ *,TYPE_3__*) ; 
 char* dup_wchar_to_utf8 (TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
dshow_cycle_pins(AVFormatContext *avctx, enum dshowDeviceType devtype,
                 enum dshowSourceFilterType sourcetype, IBaseFilter *device_filter, IPin **ppin)
{
    struct dshow_ctx *ctx = avctx->priv_data;
    IEnumPins *pins = 0;
    IPin *device_pin = NULL;
    IPin *pin;
    int r;

    const GUID *mediatype[2] = { &MEDIATYPE_Video, &MEDIATYPE_Audio };
    const char *devtypename = (devtype == VideoDevice) ? "video" : "audio only";
    const char *sourcetypename = (sourcetype == VideoSourceDevice) ? "video" : "audio";

    int set_format = (devtype == VideoDevice && (ctx->framerate ||
                                                (ctx->requested_width && ctx->requested_height) ||
                                                 ctx->pixel_format != AV_PIX_FMT_NONE ||
                                                 ctx->video_codec_id != AV_CODEC_ID_RAWVIDEO))
                  || (devtype == AudioDevice && (ctx->channels || ctx->sample_rate));
    int format_set = 0;
    int should_show_properties = (devtype == VideoDevice) ? ctx->show_video_device_dialog : ctx->show_audio_device_dialog;

    if (should_show_properties)
        dshow_show_filter_properties(device_filter, avctx);

    r = IBaseFilter_EnumPins(device_filter, &pins);
    if (r != S_OK) {
        av_log(avctx, AV_LOG_ERROR, "Could not enumerate pins.\n");
        return AVERROR(EIO);
    }

    if (!ppin) {
        av_log(avctx, AV_LOG_INFO, "DirectShow %s device options (from %s devices)\n",
               devtypename, sourcetypename);
    }

    while (!device_pin && IEnumPins_Next(pins, 1, &pin, NULL) == S_OK) {
        IKsPropertySet *p = NULL;
        IEnumMediaTypes *types = NULL;
        PIN_INFO info = {0};
        AM_MEDIA_TYPE *type;
        GUID category;
        DWORD r2;
        char *name_buf = NULL;
        wchar_t *pin_id = NULL;
        char *pin_buf = NULL;
        char *desired_pin_name = devtype == VideoDevice ? ctx->video_pin_name : ctx->audio_pin_name;

        IPin_QueryPinInfo(pin, &info);
        IBaseFilter_Release(info.pFilter);

        if (info.dir != PINDIR_OUTPUT)
            goto next;
        if (IPin_QueryInterface(pin, &IID_IKsPropertySet, (void **) &p) != S_OK)
            goto next;
        if (IKsPropertySet_Get(p, &AMPROPSETID_Pin, AMPROPERTY_PIN_CATEGORY,
                               NULL, 0, &category, sizeof(GUID), &r2) != S_OK)
            goto next;
        if (!IsEqualGUID(&category, &PIN_CATEGORY_CAPTURE))
            goto next;
        name_buf = dup_wchar_to_utf8(info.achName);

        r = IPin_QueryId(pin, &pin_id);
        if (r != S_OK) {
            av_log(avctx, AV_LOG_ERROR, "Could not query pin id\n");
            return AVERROR(EIO);
        }
        pin_buf = dup_wchar_to_utf8(pin_id);

        if (!ppin) {
            av_log(avctx, AV_LOG_INFO, " Pin \"%s\" (alternative pin name \"%s\")\n", name_buf, pin_buf);
            dshow_cycle_formats(avctx, devtype, pin, NULL);
            goto next;
        }

        if (desired_pin_name) {
            if(strcmp(name_buf, desired_pin_name) && strcmp(pin_buf, desired_pin_name)) {
                av_log(avctx, AV_LOG_DEBUG, "skipping pin \"%s\" (\"%s\") != requested \"%s\"\n",
                    name_buf, pin_buf, desired_pin_name);
                goto next;
            }
        }

        if (set_format) {
            dshow_cycle_formats(avctx, devtype, pin, &format_set);
            if (!format_set) {
                goto next;
            }
        }
        if (devtype == AudioDevice && ctx->audio_buffer_size) {
            if (dshow_set_audio_buffer_size(avctx, pin) < 0) {
                av_log(avctx, AV_LOG_ERROR, "unable to set audio buffer size %d to pin, using pin anyway...", ctx->audio_buffer_size);
            }
        }

        if (IPin_EnumMediaTypes(pin, &types) != S_OK)
            goto next;

        IEnumMediaTypes_Reset(types);
        /* in case format_set was not called, just verify the majortype */
        while (!device_pin && IEnumMediaTypes_Next(types, 1, &type, NULL) == S_OK) {
            if (IsEqualGUID(&type->majortype, mediatype[devtype])) {
                device_pin = pin;
                av_log(avctx, AV_LOG_DEBUG, "Selecting pin %s on %s\n", name_buf, devtypename);
                goto next;
            }
            CoTaskMemFree(type);
        }

next:
        if (types)
            IEnumMediaTypes_Release(types);
        if (p)
            IKsPropertySet_Release(p);
        if (device_pin != pin)
            IPin_Release(pin);
        av_free(name_buf);
        av_free(pin_buf);
        if (pin_id)
            CoTaskMemFree(pin_id);
    }

    IEnumPins_Release(pins);

    if (ppin) {
        if (set_format && !format_set) {
            av_log(avctx, AV_LOG_ERROR, "Could not set %s options\n", devtypename);
            return AVERROR(EIO);
        }
        if (!device_pin) {
            av_log(avctx, AV_LOG_ERROR,
                "Could not find output pin from %s capture device.\n", devtypename);
            return AVERROR(EIO);
        }
        *ppin = device_pin;
    }

    return 0;
}