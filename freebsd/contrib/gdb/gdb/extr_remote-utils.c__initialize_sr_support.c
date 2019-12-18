#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  sr_com ; 
 TYPE_1__ sr_settings ; 
 int /*<<< orphan*/  var_filename ; 

void
_initialize_sr_support (void)
{
/* FIXME-now: if target is open... */
  add_show_from_set (add_set_cmd ("remotedevice", no_class,
				  var_filename, (char *) &sr_settings.device,
				  "Set device for remote serial I/O.\n\
This device is used as the serial port when debugging using remote\n\
targets.", &setlist),
		     &showlist);

  add_com ("remote <command>", class_obscure, sr_com,
	   "Send a command to the remote monitor.");

}