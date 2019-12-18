#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  v_display; int /*<<< orphan*/  v_depth; int /*<<< orphan*/  v_height; int /*<<< orphan*/  v_width; int /*<<< orphan*/  v_rowBytes; scalar_t__ v_baseAddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  v_display; int /*<<< orphan*/  v_depth; int /*<<< orphan*/  v_height; int /*<<< orphan*/  v_width; int /*<<< orphan*/  v_rowBytes; scalar_t__ v_baseAddr; } ;
struct TYPE_10__ {int flags; TYPE_2__ VideoV1; TYPE_1__ Video; int /*<<< orphan*/  deviceTreeP; } ;
typedef  TYPE_4__ boot_args ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_9__ {void* v_scale; int /*<<< orphan*/  v_pixelFormat; int /*<<< orphan*/  v_display; int /*<<< orphan*/  v_depth; int /*<<< orphan*/  v_height; int /*<<< orphan*/  v_width; int /*<<< orphan*/  v_rowBytes; scalar_t__ v_baseAddr; } ;
struct TYPE_11__ {scalar_t__ initialized; void* deviceTreeHead; TYPE_3__ video; void* bootArgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTInit (void*) ; 
 scalar_t__ FALSE ; 
 TYPE_6__ PE_state ; 
 scalar_t__ TRUE ; 
 int kBootArgsFlagHiDPI ; 
 void* kPEScaleFactor1x ; 
 void* kPEScaleFactor2x ; 
 scalar_t__ ml_static_ptovirt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_identify_machine (TYPE_4__*) ; 
 int /*<<< orphan*/  pe_init_debug () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

void PE_init_platform(boolean_t vm_initialized, void * _args)
{
    boot_args *args = (boot_args *)_args;

    if (PE_state.initialized == FALSE) {
	    PE_state.initialized        = TRUE;

        // New EFI-style
        PE_state.bootArgs           = _args;
        PE_state.deviceTreeHead	    = (void *) ml_static_ptovirt(args->deviceTreeP);
        if (args->Video.v_baseAddr) {
            PE_state.video.v_baseAddr   = args->Video.v_baseAddr; // remains physical address
            PE_state.video.v_rowBytes   = args->Video.v_rowBytes;
            PE_state.video.v_width	    = args->Video.v_width;
            PE_state.video.v_height	    = args->Video.v_height;
            PE_state.video.v_depth	    = args->Video.v_depth;
            PE_state.video.v_display    = args->Video.v_display;
            strlcpy(PE_state.video.v_pixelFormat, "PPPPPPPP",
                sizeof(PE_state.video.v_pixelFormat));
        } else {
            PE_state.video.v_baseAddr   = args->VideoV1.v_baseAddr; // remains physical address
            PE_state.video.v_rowBytes   = args->VideoV1.v_rowBytes;
            PE_state.video.v_width	    = args->VideoV1.v_width;
            PE_state.video.v_height	    = args->VideoV1.v_height;
            PE_state.video.v_depth	    = args->VideoV1.v_depth;
            PE_state.video.v_display    = args->VideoV1.v_display;
            strlcpy(PE_state.video.v_pixelFormat, "PPPPPPPP",
                    sizeof(PE_state.video.v_pixelFormat));
        }

#ifdef  kBootArgsFlagHiDPI
	if (args->flags & kBootArgsFlagHiDPI)
                PE_state.video.v_scale = kPEScaleFactor2x;
	else
                PE_state.video.v_scale = kPEScaleFactor1x;
#else
	PE_state.video.v_scale = kPEScaleFactor1x;
#endif
    }

    if (!vm_initialized) {

        if (PE_state.deviceTreeHead) {
            DTInit(PE_state.deviceTreeHead);
        }

        pe_identify_machine(args);
        pe_init_debug();
    }

}