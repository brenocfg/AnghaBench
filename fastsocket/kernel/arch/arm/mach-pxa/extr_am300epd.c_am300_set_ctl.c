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
typedef  int /*<<< orphan*/  u8 ;
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
#define  BS_CS 130 
#define  BS_DC 129 
#define  BS_WR 128 
 int /*<<< orphan*/  CS_GPIO_PIN ; 
 int /*<<< orphan*/  DC_GPIO_PIN ; 
 int /*<<< orphan*/  WR_GPIO_PIN ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void am300_set_ctl(struct broadsheetfb_par *par, unsigned char bit,
				u8 state)
{
	switch (bit) {
	case BS_CS:
		gpio_set_value(CS_GPIO_PIN, state);
		break;
	case BS_DC:
		gpio_set_value(DC_GPIO_PIN, state);
		break;
	case BS_WR:
		gpio_set_value(WR_GPIO_PIN, state);
		break;
	}
}