#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ v_display; } ;
struct TYPE_3__ {TYPE_2__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  PE_initialize_console (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ PE_state ; 
 int /*<<< orphan*/  check_for_panic_log () ; 
 int /*<<< orphan*/  kPEGraphicsMode ; 
 int /*<<< orphan*/  kPETextMode ; 

void
PE_create_console(void)
{
	/*
	 * Check the head of VRAM for a panic log saved on last panic.
	 * Do this before the VRAM is trashed.
	 */
	check_for_panic_log();

	if (PE_state.video.v_display)
		PE_initialize_console(&PE_state.video, kPEGraphicsMode);
	else
		PE_initialize_console(&PE_state.video, kPETextMode);
}