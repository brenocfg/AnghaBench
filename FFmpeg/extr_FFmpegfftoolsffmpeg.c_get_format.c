#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_18__ {int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/  codec; TYPE_2__* opaque; } ;
struct TYPE_17__ {int methods; int const pix_fmt; scalar_t__ device_type; } ;
struct TYPE_16__ {int flags; } ;
struct TYPE_15__ {int const pix_fmt; scalar_t__ id; int (* init ) (TYPE_6__*) ;scalar_t__ name; } ;
struct TYPE_14__ {scalar_t__ hwaccel_id; scalar_t__ hwaccel_device_type; int hwaccel_pix_fmt; scalar_t__ hw_frames_ctx; TYPE_1__* st; int /*<<< orphan*/  file_index; } ;
struct TYPE_13__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ InputStream ;
typedef  TYPE_3__ HWAccel ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVCodecHWConfig ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int AV_PIX_FMT_FLAG_HWACCEL ; 
 int const AV_PIX_FMT_NONE ; 
 scalar_t__ HWACCEL_AUTO ; 
 scalar_t__ HWACCEL_GENERIC ; 
 int /*<<< orphan*/  av_buffer_ref (scalar_t__) ; 
 scalar_t__ av_hwdevice_get_type_name (scalar_t__) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* av_pix_fmt_desc_get (int const) ; 
 TYPE_5__* avcodec_get_hw_config (int /*<<< orphan*/ ,int) ; 
 int hwaccel_decode_init (TYPE_6__*) ; 
 TYPE_3__* hwaccels ; 
 int stub1 (TYPE_6__*) ; 

__attribute__((used)) static enum AVPixelFormat get_format(AVCodecContext *s, const enum AVPixelFormat *pix_fmts)
{
    InputStream *ist = s->opaque;
    const enum AVPixelFormat *p;
    int ret;

    for (p = pix_fmts; *p != AV_PIX_FMT_NONE; p++) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(*p);
        const AVCodecHWConfig  *config = NULL;
        int i;

        if (!(desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            break;

        if (ist->hwaccel_id == HWACCEL_GENERIC ||
            ist->hwaccel_id == HWACCEL_AUTO) {
            for (i = 0;; i++) {
                config = avcodec_get_hw_config(s->codec, i);
                if (!config)
                    break;
                if (!(config->methods &
                      AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX))
                    continue;
                if (config->pix_fmt == *p)
                    break;
            }
        }
        if (config) {
            if (config->device_type != ist->hwaccel_device_type) {
                // Different hwaccel offered, ignore.
                continue;
            }

            ret = hwaccel_decode_init(s);
            if (ret < 0) {
                if (ist->hwaccel_id == HWACCEL_GENERIC) {
                    av_log(NULL, AV_LOG_FATAL,
                           "%s hwaccel requested for input stream #%d:%d, "
                           "but cannot be initialized.\n",
                           av_hwdevice_get_type_name(config->device_type),
                           ist->file_index, ist->st->index);
                    return AV_PIX_FMT_NONE;
                }
                continue;
            }
        } else {
            const HWAccel *hwaccel = NULL;
            int i;
            for (i = 0; hwaccels[i].name; i++) {
                if (hwaccels[i].pix_fmt == *p) {
                    hwaccel = &hwaccels[i];
                    break;
                }
            }
            if (!hwaccel) {
                // No hwaccel supporting this pixfmt.
                continue;
            }
            if (hwaccel->id != ist->hwaccel_id) {
                // Does not match requested hwaccel.
                continue;
            }

            ret = hwaccel->init(s);
            if (ret < 0) {
                av_log(NULL, AV_LOG_FATAL,
                       "%s hwaccel requested for input stream #%d:%d, "
                       "but cannot be initialized.\n", hwaccel->name,
                       ist->file_index, ist->st->index);
                return AV_PIX_FMT_NONE;
            }
        }

        if (ist->hw_frames_ctx) {
            s->hw_frames_ctx = av_buffer_ref(ist->hw_frames_ctx);
            if (!s->hw_frames_ctx)
                return AV_PIX_FMT_NONE;
        }

        ist->hwaccel_pix_fmt = *p;
        break;
    }

    return *p;
}