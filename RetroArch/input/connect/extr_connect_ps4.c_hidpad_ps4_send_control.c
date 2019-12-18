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
struct hidpad_ps4_data {int slot; int /*<<< orphan*/  connection; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  report_buffer ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_control ) (int /*<<< orphan*/ ,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void hidpad_ps4_send_control(struct hidpad_ps4_data* device)
{
   /* TODO: Can this be modified to turn off motion tracking? */
   static uint8_t report_buffer[79] = {
      0x52, 0x11, 0xB0, 0x00, 0x0F
   };

#if 0
   uint8_t rgb[4][3] = { { 0xFF, 0, 0 }, { 0, 0xFF, 0 }, { 0, 0, 0xFF }, { 0xFF, 0xFF, 0xFF } };
   report_buffer[ 9] = rgb[(device->slot % 4)][0];
   report_buffer[10] = rgb[(device->slot % 4)][1];
   report_buffer[11] = rgb[(device->slot % 4)][2];
#endif

   device->driver->send_control(device->connection,
         report_buffer, sizeof(report_buffer));
}