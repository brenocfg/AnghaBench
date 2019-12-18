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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;
struct ar5416IniArray {int ia_columns; unsigned int ia_rows; int /*<<< orphan*/  ia_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  DO_DELAY (unsigned int) ; 
 int /*<<< orphan*/  INI_RA (struct ar5416IniArray*,unsigned int,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9003_hw_prog_ini(struct ath_hw *ah,
			       struct ar5416IniArray *iniArr,
			       int column)
{
	unsigned int i, regWrites = 0;

	/* New INI format: Array may be undefined (pre, core, post arrays) */
	if (!iniArr->ia_array)
		return;

	/*
	 * New INI format: Pre, core, and post arrays for a given subsystem
	 * may be modal (> 2 columns) or non-modal (2 columns). Determine if
	 * the array is non-modal and force the column to 1.
	 */
	if (column >= iniArr->ia_columns)
		column = 1;

	for (i = 0; i < iniArr->ia_rows; i++) {
		u32 reg = INI_RA(iniArr, i, 0);
		u32 val = INI_RA(iniArr, i, column);

		REG_WRITE(ah, reg, val);

		DO_DELAY(regWrites);
	}
}