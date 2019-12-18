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
struct TYPE_3__ {int /*<<< orphan*/  loadflags; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUIET_FLAG ; 
 TYPE_2__ boot_params ; 
 scalar_t__ cmdline_find_option_bool (char*) ; 
 int /*<<< orphan*/  copy_boot_params () ; 
 int /*<<< orphan*/  detect_memory () ; 
 int /*<<< orphan*/  die () ; 
 int /*<<< orphan*/  go_to_protected_mode () ; 
 int /*<<< orphan*/  init_heap () ; 
 int /*<<< orphan*/  keyboard_set_repeat () ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  query_apm_bios () ; 
 int /*<<< orphan*/  query_edd () ; 
 int /*<<< orphan*/  query_ist () ; 
 int /*<<< orphan*/  query_mca () ; 
 int /*<<< orphan*/  set_bios_mode () ; 
 int /*<<< orphan*/  set_video () ; 
 scalar_t__ validate_cpu () ; 

void main(void)
{
	/* First, copy the boot header into the "zeropage" */
	copy_boot_params();

	/* End of heap check */
	init_heap();

	/* Make sure we have all the proper CPU support */
	if (validate_cpu()) {
		puts("Unable to boot - please use a kernel appropriate "
		     "for your CPU.\n");
		die();
	}

	/* Tell the BIOS what CPU mode we intend to run in. */
	set_bios_mode();

	/* Detect memory layout */
	detect_memory();

	/* Set keyboard repeat rate (why?) */
	keyboard_set_repeat();

	/* Query MCA information */
	query_mca();

	/* Query Intel SpeedStep (IST) information */
	query_ist();

	/* Query APM information */
#if defined(CONFIG_APM) || defined(CONFIG_APM_MODULE)
	query_apm_bios();
#endif

	/* Query EDD information */
#if defined(CONFIG_EDD) || defined(CONFIG_EDD_MODULE)
	query_edd();
#endif

	/* Set the video mode */
	set_video();

	/* Parse command line for 'quiet' and pass it to decompressor. */
	if (cmdline_find_option_bool("quiet"))
		boot_params.hdr.loadflags |= QUIET_FLAG;

	/* Do the last things and invoke protected mode */
	go_to_protected_mode();
}