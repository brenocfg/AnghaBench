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
struct hidpad_wiiupro_data {int /*<<< orphan*/  connection; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  report_buffer ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_control ) (int /*<<< orphan*/ ,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void hidpad_wiiupro_send_control(struct hidpad_wiiupro_data* device)
{
   /* 0x12 = Set data report; 0x34 = All buttons and analogs */
   static uint8_t report_buffer[4] = { 0xA2, 0x12, 0x00, 0x34 };
   device->driver->send_control(device->connection,
         report_buffer, sizeof(report_buffer));
}