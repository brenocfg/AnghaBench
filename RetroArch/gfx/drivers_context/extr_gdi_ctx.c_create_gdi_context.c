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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int g_win32_inited ; 
 int /*<<< orphan*/  win32_gdi_hdc ; 
 int /*<<< orphan*/  win32_setup_pixel_format (int /*<<< orphan*/ ,int) ; 

void create_gdi_context(HWND hwnd, bool *quit)
{
   win32_gdi_hdc = GetDC(hwnd);

   win32_setup_pixel_format(win32_gdi_hdc, false);

   g_win32_inited = true;
}