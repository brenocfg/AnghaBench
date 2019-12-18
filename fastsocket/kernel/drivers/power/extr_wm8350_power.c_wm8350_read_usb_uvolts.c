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
struct wm8350 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_AUXADC_USB ; 
 int WM8350_AUX_COEFF ; 
 int wm8350_read_auxadc (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_read_usb_uvolts(struct wm8350 *wm8350)
{
	return wm8350_read_auxadc(wm8350, WM8350_AUXADC_USB, 0, 0)
		* WM8350_AUX_COEFF;
}