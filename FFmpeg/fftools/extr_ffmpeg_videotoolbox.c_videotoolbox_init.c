#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  tmp_frame; } ;
typedef  TYPE_1__ VTContext ;
struct TYPE_16__ {TYPE_2__* opaque; } ;
struct TYPE_15__ {int /*<<< orphan*/  cv_pix_fmt_type; } ;
struct TYPE_14__ {scalar_t__ hwaccel_id; int /*<<< orphan*/  hwaccel_retrieve_data; int /*<<< orphan*/  (* hwaccel_uninit ) (TYPE_4__*) ;TYPE_1__* hwaccel_ctx; } ;
typedef  TYPE_2__ InputStream ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  TYPE_3__ AVVideotoolboxContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_LOG_ERROR ; 
 int AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFStringCreateWithCString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ HWACCEL_AUTO ; 
 int /*<<< orphan*/  UTGetOSTypeFromString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_alloc () ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int,char*,...) ; 
 TYPE_1__* av_mallocz (int) ; 
 TYPE_3__* av_videotoolbox_alloc_context () ; 
 int av_videotoolbox_default_init (TYPE_4__*) ; 
 int av_videotoolbox_default_init2 (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  videotoolbox_pixfmt ; 
 int /*<<< orphan*/  videotoolbox_retrieve_data ; 
 int /*<<< orphan*/  videotoolbox_uninit (TYPE_4__*) ; 

int videotoolbox_init(AVCodecContext *s)
{
    InputStream *ist = s->opaque;
    int loglevel = (ist->hwaccel_id == HWACCEL_AUTO) ? AV_LOG_VERBOSE : AV_LOG_ERROR;
    int ret = 0;
    VTContext *vt;

    vt = av_mallocz(sizeof(*vt));
    if (!vt)
        return AVERROR(ENOMEM);

    ist->hwaccel_ctx           = vt;
    ist->hwaccel_uninit        = videotoolbox_uninit;
    ist->hwaccel_retrieve_data = videotoolbox_retrieve_data;

    vt->tmp_frame = av_frame_alloc();
    if (!vt->tmp_frame) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    // TODO: reindent
        if (!videotoolbox_pixfmt) {
            ret = av_videotoolbox_default_init(s);
        } else {
            AVVideotoolboxContext *vtctx = av_videotoolbox_alloc_context();
            CFStringRef pixfmt_str = CFStringCreateWithCString(kCFAllocatorDefault,
                                                               videotoolbox_pixfmt,
                                                               kCFStringEncodingUTF8);
#if HAVE_UTGETOSTYPEFROMSTRING
            vtctx->cv_pix_fmt_type = UTGetOSTypeFromString(pixfmt_str);
#else
            av_log(s, loglevel, "UTGetOSTypeFromString() is not available "
                   "on this platform, %s pixel format can not be honored from "
                   "the command line\n", videotoolbox_pixfmt);
#endif
            ret = av_videotoolbox_default_init2(s, vtctx);
            CFRelease(pixfmt_str);
        }
    if (ret < 0) {
        av_log(NULL, loglevel, "Error creating Videotoolbox decoder.\n");
        goto fail;
    }

    return 0;
fail:
    videotoolbox_uninit(s);
    return ret;
}