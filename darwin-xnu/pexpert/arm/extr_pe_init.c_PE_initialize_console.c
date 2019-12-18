#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  v_scale; } ;
struct TYPE_9__ {TYPE_1__ video; } ;
struct TYPE_8__ {int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
typedef  TYPE_1__ PE_Video ;

/* Variables and functions */
 TYPE_5__ PE_state ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ appleClut8 ; 
 TYPE_2__ default_progress ; 
 int /*<<< orphan*/  default_progress_data1x ; 
 int /*<<< orphan*/  default_progress_data2x ; 
 int /*<<< orphan*/  default_progress_data3x ; 
 int /*<<< orphan*/  initialize_screen (TYPE_1__*,int) ; 
#define  kPEDisableScreen 130 
#define  kPEEnableScreen 129 
#define  kPEReleaseScreen 128 
 int /*<<< orphan*/  kprintf (char*,int) ; 
 int /*<<< orphan*/  switch_to_old_console (int) ; 
 int switch_to_serial_console () ; 
 int /*<<< orphan*/  vc_progress_initialize (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  vc_progress_initialized ; 

int
PE_initialize_console(PE_Video * info, int op)
{
	static int last_console = -1;

	if (info && (info != &PE_state.video)) info->v_scale = PE_state.video.v_scale;

	switch (op) {

	case kPEDisableScreen:
		initialize_screen(info, op);
		last_console = switch_to_serial_console();
		kprintf("kPEDisableScreen %d\n", last_console);
		break;

	case kPEEnableScreen:
		initialize_screen(info, op);
		if (info)
			PE_state.video = *info;
		kprintf("kPEEnableScreen %d\n", last_console);
		if (last_console != -1)
			switch_to_old_console(last_console);
		break;

	case kPEReleaseScreen:
		/*
		 * we don't show the progress indicator on boot, but want to
		 * show it afterwards.
		 */
		if (!vc_progress_initialized) {
			default_progress.dx = 0;
			default_progress.dy = 0;
			vc_progress_initialize(&default_progress,
					       default_progress_data1x, 
					       default_progress_data2x,
					       default_progress_data3x,
					       (unsigned char *) appleClut8);
			vc_progress_initialized = TRUE;
		}
		initialize_screen(info, op);
		break;

	default:
		initialize_screen(info, op);
		break;
	}

	return 0;
}