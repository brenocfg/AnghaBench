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
typedef  int uint8_t ;
struct hidpad_ps3_data {int slot; int* motors; int /*<<< orphan*/  connection; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  report_buffer ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_control ) (int /*<<< orphan*/ ,int*,int) ;int /*<<< orphan*/  (* set_report ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DS3_RUMBLE_REPORT_ID ; 
 int /*<<< orphan*/  HID_REPORT_OUTPUT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void hidpad_ps3_send_control(struct hidpad_ps3_data* device)
{
   /* TODO: Can this be modified to turn off motion tracking? */
   static uint8_t report_buffer[] = {
      0x52, 0x01,
      0x00, 0xFF, 0x00, 0xFF, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00,
      0xff, 0x27, 0x10, 0x00, 0x32,
      0xff, 0x27, 0x10, 0x00, 0x32,
      0xff, 0x27, 0x10, 0x00, 0x32,
      0xff, 0x27, 0x10, 0x00, 0x32,
      0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   };

   /* Turn on the appropriate LED */
   report_buffer[11] = 1 << ((device->slot % 4) + 1);
   /* Set rumble state */
   report_buffer[4]  = device->motors[1] >> 8;
   report_buffer[6]  = device->motors[0] >> 8;
#ifdef HAVE_WIIUSB_HID
   report_buffer[1]  = 0x03; /* send control message type */
   device->driver->send_control(device->connection, &report_buffer[1], sizeof(report_buffer)-1);
#elif defined(WIIU)
   device->driver->set_report(device->connection,
                              HID_REPORT_OUTPUT,
                              DS3_RUMBLE_REPORT_ID,
                              report_buffer+2,
                              sizeof(report_buffer) - (2*sizeof(uint8_t)));
#else
   device->driver->send_control(device->connection, report_buffer, sizeof(report_buffer));
#endif
}