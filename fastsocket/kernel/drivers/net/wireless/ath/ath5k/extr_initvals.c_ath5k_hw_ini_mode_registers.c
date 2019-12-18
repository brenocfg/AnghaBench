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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ath5k_ini_mode {scalar_t__ mode_register; int /*<<< orphan*/ * mode_value; } ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_REG_WAIT (unsigned int) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath5k_hw_ini_mode_registers(struct ath5k_hw *ah,
		unsigned int size, const struct ath5k_ini_mode *ini_mode,
		u8 mode)
{
	unsigned int i;

	for (i = 0; i < size; i++) {
		AR5K_REG_WAIT(i);
		ath5k_hw_reg_write(ah, ini_mode[i].mode_value[mode],
			(u32)ini_mode[i].mode_register);
	}

}