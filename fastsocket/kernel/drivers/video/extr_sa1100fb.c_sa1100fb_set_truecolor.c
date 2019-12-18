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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int /*<<< orphan*/  ASSABET_BCR_LCD_12RGB ; 
 int /*<<< orphan*/  ASSABET_BCR_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSABET_BCR_set (int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_assabet () ; 

__attribute__((used)) static inline void sa1100fb_set_truecolor(u_int is_true_color)
{
	if (machine_is_assabet()) {
#if 1		// phase 4 or newer Assabet's
		if (is_true_color)
			ASSABET_BCR_set(ASSABET_BCR_LCD_12RGB);
		else
			ASSABET_BCR_clear(ASSABET_BCR_LCD_12RGB);
#else
		// older Assabet's
		if (is_true_color)
			ASSABET_BCR_clear(ASSABET_BCR_LCD_12RGB);
		else
			ASSABET_BCR_set(ASSABET_BCR_LCD_12RGB);
#endif
	}
}