#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ mfxVersion ;
typedef  int /*<<< orphan*/  mfxSession ;
typedef  int /*<<< orphan*/  mfxIMPL ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int MFXInit (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MFXQueryIMPL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MFX_IMPL_AUTO_ANY ; 
 int MFX_IMPL_BASETYPE (int /*<<< orphan*/ ) ; 
#define  MFX_IMPL_HARDWARE 132 
#define  MFX_IMPL_HARDWARE2 131 
#define  MFX_IMPL_HARDWARE3 130 
#define  MFX_IMPL_HARDWARE4 129 
#define  MFX_IMPL_SOFTWARE 128 
 int /*<<< orphan*/  QSV_VERSION_MAJOR ; 
 int /*<<< orphan*/  QSV_VERSION_MINOR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int ff_qsv_print_error (int /*<<< orphan*/ *,int,char*) ; 
 int qsv_load_plugins (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

int ff_qsv_init_internal_session(AVCodecContext *avctx, mfxSession *session,
                                 const char *load_plugins)
{
    mfxIMPL impl   = MFX_IMPL_AUTO_ANY;
    mfxVersion ver = { { QSV_VERSION_MINOR, QSV_VERSION_MAJOR } };

    const char *desc;
    int ret;

    ret = MFXInit(impl, &ver, session);
    if (ret < 0)
        return ff_qsv_print_error(avctx, ret,
                                  "Error initializing an internal MFX session");

    ret = qsv_load_plugins(*session, load_plugins, avctx);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error loading plugins\n");
        return ret;
    }

    MFXQueryIMPL(*session, &impl);

    switch (MFX_IMPL_BASETYPE(impl)) {
    case MFX_IMPL_SOFTWARE:
        desc = "software";
        break;
    case MFX_IMPL_HARDWARE:
    case MFX_IMPL_HARDWARE2:
    case MFX_IMPL_HARDWARE3:
    case MFX_IMPL_HARDWARE4:
        desc = "hardware accelerated";
        break;
    default:
        desc = "unknown";
    }

    av_log(avctx, AV_LOG_VERBOSE,
           "Initialized an internal MFX session using %s implementation\n",
           desc);

    return 0;
}