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
typedef  int /*<<< orphan*/  sb_devc ;

/* Variables and functions */
 int ess_getmixer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ess_setmixer (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int ess_probe (sb_devc * devc, int reg, int xorval)
{
	int  val1, val2, val3;

	val1 = ess_getmixer (devc, reg);
	val2 = val1 ^ xorval;
	ess_setmixer (devc, reg, val2);
	val3 = ess_getmixer (devc, reg);
	ess_setmixer (devc, reg, val1);

	return (val2 == val3);
}