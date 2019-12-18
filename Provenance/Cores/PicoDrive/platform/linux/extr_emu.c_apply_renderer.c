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
struct TYPE_2__ {int renderer; } ;

/* Variables and functions */
 int PAHW_32X ; 
 int /*<<< orphan*/  PDF_8BIT ; 
 int /*<<< orphan*/  PDF_NONE ; 
 int /*<<< orphan*/  PDF_RGB555 ; 
 int /*<<< orphan*/  POPT_ALT_RENDERER ; 
 int PicoAHW ; 
 int /*<<< orphan*/  PicoDraw2FB ; 
 int /*<<< orphan*/  PicoDrawSetOutBuf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PicoDrawSetOutFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoOpt ; 
#define  RT_16BIT 130 
#define  RT_8BIT_ACC 129 
#define  RT_8BIT_FAST 128 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 int g_screen_width ; 

__attribute__((used)) static void apply_renderer(void)
{
	switch (currentConfig.renderer) {
	case RT_16BIT:
		PicoOpt &= ~POPT_ALT_RENDERER;
		PicoDrawSetOutFormat(PDF_RGB555, 0);
		PicoDrawSetOutBuf(g_screen_ptr, g_screen_width * 2);
		break;
	case RT_8BIT_ACC:
		PicoOpt &= ~POPT_ALT_RENDERER;
		PicoDrawSetOutFormat(PDF_8BIT, 0);
		PicoDrawSetOutBuf(PicoDraw2FB + 8, 328);
		break;
	case RT_8BIT_FAST:
		PicoOpt |=  POPT_ALT_RENDERER;
		PicoDrawSetOutFormat(PDF_NONE, 0);
		break;
	}

	if (PicoAHW & PAHW_32X)
		PicoDrawSetOutBuf(g_screen_ptr, g_screen_width * 2);
}