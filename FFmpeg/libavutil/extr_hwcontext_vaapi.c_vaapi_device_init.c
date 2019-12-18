#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  scalar_t__ VAStatus ;
struct TYPE_15__ {unsigned int fourcc; } ;
typedef  TYPE_2__ VAImageFormat ;
struct TYPE_16__ {size_t nb_formats; TYPE_10__* formats; } ;
typedef  TYPE_3__ VAAPIDeviceContext ;
struct TYPE_19__ {int quirks; int /*<<< orphan*/  friendly_name; int /*<<< orphan*/  match_string; } ;
struct TYPE_18__ {TYPE_4__* hwctx; TYPE_1__* internal; } ;
struct TYPE_17__ {int driver_quirks; int /*<<< orphan*/  display; } ;
struct TYPE_14__ {TYPE_3__* priv; } ;
struct TYPE_13__ {int pix_fmt; TYPE_2__ image_format; } ;
typedef  TYPE_4__ AVVAAPIDeviceContext ;
typedef  TYPE_5__ AVHWDeviceContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int AV_PIX_FMT_NONE ; 
 int AV_VAAPI_DRIVER_QUIRK_USER_SET ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (TYPE_6__*) ; 
 scalar_t__ VA_STATUS_SUCCESS ; 
 int /*<<< orphan*/  av_free (TYPE_2__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_10__**) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 void* av_malloc (int) ; 
 scalar_t__ strstr (char const*,int /*<<< orphan*/ ) ; 
 int vaMaxNumImageFormats (int /*<<< orphan*/ ) ; 
 scalar_t__ vaQueryImageFormats (int /*<<< orphan*/ ,TYPE_2__*,int*) ; 
 char* vaQueryVendorString (int /*<<< orphan*/ ) ; 
 TYPE_6__* vaapi_driver_quirks_table ; 
 int vaapi_pix_fmt_from_fourcc (unsigned int) ; 

__attribute__((used)) static int vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->internal->priv;
    AVVAAPIDeviceContext *hwctx = hwdev->hwctx;
    VAImageFormat *image_list = NULL;
    VAStatus vas;
    const char *vendor_string;
    int err, i, image_count;
    enum AVPixelFormat pix_fmt;
    unsigned int fourcc;

    image_count = vaMaxNumImageFormats(hwctx->display);
    if (image_count <= 0) {
        err = AVERROR(EIO);
        goto fail;
    }
    image_list = av_malloc(image_count * sizeof(*image_list));
    if (!image_list) {
        err = AVERROR(ENOMEM);
        goto fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_count);
    if (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        goto fail;
    }

    ctx->formats  = av_malloc(image_count * sizeof(*ctx->formats));
    if (!ctx->formats) {
        err = AVERROR(ENOMEM);
        goto fail;
    }
    ctx->nb_formats = 0;
    for (i = 0; i < image_count; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        if (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } else {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    if (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    if (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } else {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        if (vendor_string) {
            for (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                if (strstr(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    break;
                }
            }
            if (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } else {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    return 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    return err;
}