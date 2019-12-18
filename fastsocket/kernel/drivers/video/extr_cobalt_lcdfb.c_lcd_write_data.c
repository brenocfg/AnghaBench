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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct fb_info {scalar_t__ screen_base; } ;

/* Variables and functions */
 scalar_t__ LCD_DATA_REG_OFFSET ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void lcd_write_data(struct fb_info *info, u8 data)
{
	writel((u32)data << 24, info->screen_base + LCD_DATA_REG_OFFSET);
}