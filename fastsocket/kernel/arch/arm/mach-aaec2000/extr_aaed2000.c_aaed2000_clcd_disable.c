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
struct clcd_fb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAED_EGPIO_LCD_PWR_EN ; 
 int /*<<< orphan*/  AAED_EXT_GPIO ; 

__attribute__((used)) static void aaed2000_clcd_disable(struct clcd_fb *fb)
{
	AAED_EXT_GPIO &= ~AAED_EGPIO_LCD_PWR_EN;
}