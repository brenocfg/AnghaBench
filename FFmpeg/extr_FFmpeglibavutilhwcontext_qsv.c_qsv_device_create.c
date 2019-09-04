#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxIMPL ;
typedef  enum AVHWDeviceType { ____Placeholder_AVHWDeviceType } AVHWDeviceType ;
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_13__ {int /*<<< orphan*/ * value; } ;
struct TYPE_12__ {int /*<<< orphan*/  free; TYPE_1__* user_opaque; } ;
struct TYPE_11__ {TYPE_9__* child_device_ctx; } ;
typedef  TYPE_1__ QSVDevicePriv ;
typedef  TYPE_2__ AVHWDeviceContext ;
typedef  TYPE_3__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_HWDEVICE_TYPE_DXVA2 ; 
 int AV_HWDEVICE_TYPE_VAAPI ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ CONFIG_DXVA2 ; 
 scalar_t__ CONFIG_VAAPI ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 TYPE_3__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int av_hwdevice_ctx_create (TYPE_9__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  choose_implementation (char const*) ; 
 int qsv_device_derive_from_child (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsv_device_free ; 

__attribute__((used)) static int qsv_device_create(AVHWDeviceContext *ctx, const char *device,
                             AVDictionary *opts, int flags)
{
    QSVDevicePriv *priv;
    enum AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    int ret;

    priv = av_mallocz(sizeof(*priv));
    if (!priv)
        return AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->free        = qsv_device_free;

    e = av_dict_get(opts, "child_device", NULL, 0);

    if (CONFIG_VAAPI)
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    else if (CONFIG_DXVA2)
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    else {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        return AVERROR(ENOSYS);
    }

    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->value : NULL, NULL, 0);
    if (ret < 0)
        return ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device);

    return qsv_device_derive_from_child(ctx, impl, child_device, 0);
}