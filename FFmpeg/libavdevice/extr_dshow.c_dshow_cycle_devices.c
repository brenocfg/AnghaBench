#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dshow_ctx {char** device_name; int video_device_number; int audio_device_number; } ;
typedef  enum dshowSourceFilterType { ____Placeholder_dshowSourceFilterType } dshowSourceFilterType ;
typedef  enum dshowDeviceType { ____Placeholder_dshowDeviceType } dshowDeviceType ;
struct TYPE_6__ {int /*<<< orphan*/ * bstrVal; int /*<<< orphan*/  vt; } ;
typedef  TYPE_1__ VARIANT ;
struct TYPE_7__ {struct dshow_ctx* priv_data; } ;
typedef  int /*<<< orphan*/ * LPOLESTR ;
typedef  int /*<<< orphan*/ * LPMALLOC ;
typedef  int /*<<< orphan*/  IPropertyBag ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IEnumMoniker ;
typedef  int /*<<< orphan*/  ICreateDevEnum ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  int /*<<< orphan*/  GUID ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  const CLSID_AudioInputDeviceCategory ; 
 int /*<<< orphan*/  const CLSID_VideoInputDeviceCategory ; 
 int CoGetMalloc (int,int /*<<< orphan*/ **) ; 
 int CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int ICreateDevEnum_CreateClassEnumerator (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int IEnumMoniker_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBaseFilter ; 
 int /*<<< orphan*/  IID_IPropertyBag ; 
 int /*<<< orphan*/  IMalloc_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IMoniker_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int IMoniker_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int IPropertyBag_Read (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPropertyBag_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  VT_BSTR ; 
 int VideoDevice ; 
 int VideoSourceDevice ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* dup_wchar_to_utf8 (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
dshow_cycle_devices(AVFormatContext *avctx, ICreateDevEnum *devenum,
                    enum dshowDeviceType devtype, enum dshowSourceFilterType sourcetype,
                    IBaseFilter **pfilter, char **device_unique_name)
{
    struct dshow_ctx *ctx = avctx->priv_data;
    IBaseFilter *device_filter = NULL;
    IEnumMoniker *classenum = NULL;
    IMoniker *m = NULL;
    const char *device_name = ctx->device_name[devtype];
    int skip = (devtype == VideoDevice) ? ctx->video_device_number
                                        : ctx->audio_device_number;
    int r;

    const GUID *device_guid[2] = { &CLSID_VideoInputDeviceCategory,
                                   &CLSID_AudioInputDeviceCategory };
    const char *devtypename = (devtype == VideoDevice) ? "video" : "audio only";
    const char *sourcetypename = (sourcetype == VideoSourceDevice) ? "video" : "audio";

    r = ICreateDevEnum_CreateClassEnumerator(devenum, device_guid[sourcetype],
                                             (IEnumMoniker **) &classenum, 0);
    if (r != S_OK) {
        av_log(avctx, AV_LOG_ERROR, "Could not enumerate %s devices (or none found).\n",
               devtypename);
        return AVERROR(EIO);
    }

    while (!device_filter && IEnumMoniker_Next(classenum, 1, &m, NULL) == S_OK) {
        IPropertyBag *bag = NULL;
        char *friendly_name = NULL;
        char *unique_name = NULL;
        VARIANT var;
        IBindCtx *bind_ctx = NULL;
        LPOLESTR olestr = NULL;
        LPMALLOC co_malloc = NULL;
        int i;

        r = CoGetMalloc(1, &co_malloc);
        if (r != S_OK)
            goto fail1;
        r = CreateBindCtx(0, &bind_ctx);
        if (r != S_OK)
            goto fail1;
        /* GetDisplayname works for both video and audio, DevicePath doesn't */
        r = IMoniker_GetDisplayName(m, bind_ctx, NULL, &olestr);
        if (r != S_OK)
            goto fail1;
        unique_name = dup_wchar_to_utf8(olestr);
        /* replace ':' with '_' since we use : to delineate between sources */
        for (i = 0; i < strlen(unique_name); i++) {
            if (unique_name[i] == ':')
                unique_name[i] = '_';
        }

        r = IMoniker_BindToStorage(m, 0, 0, &IID_IPropertyBag, (void *) &bag);
        if (r != S_OK)
            goto fail1;

        var.vt = VT_BSTR;
        r = IPropertyBag_Read(bag, L"FriendlyName", &var, NULL);
        if (r != S_OK)
            goto fail1;
        friendly_name = dup_wchar_to_utf8(var.bstrVal);

        if (pfilter) {
            if (strcmp(device_name, friendly_name) && strcmp(device_name, unique_name))
                goto fail1;

            if (!skip--) {
                r = IMoniker_BindToObject(m, 0, 0, &IID_IBaseFilter, (void *) &device_filter);
                if (r != S_OK) {
                    av_log(avctx, AV_LOG_ERROR, "Unable to BindToObject for %s\n", device_name);
                    goto fail1;
                }
                *device_unique_name = unique_name;
                unique_name = NULL;
                // success, loop will end now
            }
        } else {
            av_log(avctx, AV_LOG_INFO, " \"%s\"\n", friendly_name);
            av_log(avctx, AV_LOG_INFO, "    Alternative name \"%s\"\n", unique_name);
        }

fail1:
        if (olestr && co_malloc)
            IMalloc_Free(co_malloc, olestr);
        if (bind_ctx)
            IBindCtx_Release(bind_ctx);
        av_freep(&friendly_name);
        av_freep(&unique_name);
        if (bag)
            IPropertyBag_Release(bag);
        IMoniker_Release(m);
    }

    IEnumMoniker_Release(classenum);

    if (pfilter) {
        if (!device_filter) {
            av_log(avctx, AV_LOG_ERROR, "Could not find %s device with name [%s] among source devices of type %s.\n",
                   devtypename, device_name, sourcetypename);
            return AVERROR(EIO);
        }
        *pfilter = device_filter;
    }

    return 0;
}