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
typedef  int u32 ;
struct TYPE_2__ {void (* lcdc_callback ) (void*) ;int /*<<< orphan*/  tearsync_mode; void* lcdc_callback_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFBI_CONTROL ; 
 int /*<<< orphan*/  RFBI_PIXEL_CNT ; 
 int /*<<< orphan*/  omap_dispc_enable_lcd_out (int) ; 
 int /*<<< orphan*/  omap_dispc_set_lcd_size (int,int) ; 
 TYPE_1__ rfbi ; 
 int /*<<< orphan*/  rfbi_enable_clocks (int) ; 
 int rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rfbi_transfer_area(int width, int height,
				void (callback)(void * data), void *data)
{
	u32 w;

	BUG_ON(callback == NULL);

	rfbi_enable_clocks(1);
	omap_dispc_set_lcd_size(width, height);

	rfbi.lcdc_callback = callback;
	rfbi.lcdc_callback_data = data;

	rfbi_write_reg(RFBI_PIXEL_CNT, width * height);

	w = rfbi_read_reg(RFBI_CONTROL);
	w |= 1;				/* enable */
	if (!rfbi.tearsync_mode)
		w |= 1 << 4;		/* internal trigger, reset by HW */
	rfbi_write_reg(RFBI_CONTROL, w);

	omap_dispc_enable_lcd_out(1);
}