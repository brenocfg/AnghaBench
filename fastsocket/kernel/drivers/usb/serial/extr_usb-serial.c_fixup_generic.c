#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_serial_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chars_in_buffer ; 
 int /*<<< orphan*/  close ; 
 int /*<<< orphan*/  disconnect ; 
 int /*<<< orphan*/  open ; 
 int /*<<< orphan*/  read_bulk_callback ; 
 int /*<<< orphan*/  release ; 
 int /*<<< orphan*/  set_to_generic_if_null (struct usb_serial_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write ; 
 int /*<<< orphan*/  write_bulk_callback ; 
 int /*<<< orphan*/  write_room ; 

__attribute__((used)) static void fixup_generic(struct usb_serial_driver *device)
{
	set_to_generic_if_null(device, open);
	set_to_generic_if_null(device, write);
	set_to_generic_if_null(device, close);
	set_to_generic_if_null(device, write_room);
	set_to_generic_if_null(device, chars_in_buffer);
	set_to_generic_if_null(device, read_bulk_callback);
	set_to_generic_if_null(device, write_bulk_callback);
	set_to_generic_if_null(device, disconnect);
	set_to_generic_if_null(device, release);
}