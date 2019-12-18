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

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_rate_100 ; 
 int /*<<< orphan*/  lcd_rate_120 ; 
 int* memregs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_reg_setting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int mmsp2_lcdrate_set(int is_pal)
{
	if (memregs[0x2800>>1] & 0x100) // tv-out
		return 0;

	printf("setting custom LCD refresh (%d Hz)... ", is_pal ? 100 : 120);
	fflush(stdout);

	set_reg_setting(is_pal ? lcd_rate_100 : lcd_rate_120);
	printf("done.\n");
	return 0;
}