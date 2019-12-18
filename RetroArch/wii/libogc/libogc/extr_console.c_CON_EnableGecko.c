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

/* Variables and functions */
 size_t STD_ERR ; 
 size_t STD_OUT ; 
 int /*<<< orphan*/  _IOLBF ; 
 int __gecko_safe ; 
 int __gecko_status ; 
 int /*<<< orphan*/  curr_con ; 
 int /*<<< orphan*/ ** devoptab_list ; 
 int /*<<< orphan*/  dotab_stdout ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usb_isgeckoalive (int) ; 

void CON_EnableGecko(int channel,int safe)
{
	if(channel && (channel>1 || !usb_isgeckoalive(channel))) channel = -1;

	__gecko_status = channel;
	__gecko_safe = safe;

	if(__gecko_status!=-1) {
		devoptab_list[STD_OUT] = &dotab_stdout;
		devoptab_list[STD_ERR] = &dotab_stdout;

		// line buffered output for threaded apps when only using the usbgecko
		if(!curr_con) {
			setvbuf(stdout, NULL, _IOLBF, 0);
			setvbuf(stderr, NULL, _IOLBF, 0);
		}
	}
}