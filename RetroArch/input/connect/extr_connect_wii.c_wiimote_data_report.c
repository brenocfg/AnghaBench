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
typedef  int uint8_t ;
struct connect_wii_wiimote_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM_CMD_REPORT_TYPE ; 
 int /*<<< orphan*/  wiimote_is_connected (struct connect_wii_wiimote_t*) ; 
 int /*<<< orphan*/  wiimote_send (struct connect_wii_wiimote_t*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void wiimote_data_report(struct connect_wii_wiimote_t* wm, uint8_t type)
{
   uint8_t buf[2] = {0x0,0x0};

   if (!wm  || !wiimote_is_connected(wm))
      return;

   buf[1] = type;

   /* CUIDADO es un &buf? */
   wiimote_send(wm, WM_CMD_REPORT_TYPE, buf, 2);
}