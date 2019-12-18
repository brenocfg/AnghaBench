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
struct tas {int drc_range; scalar_t__ drc_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAS_REG_DRC ; 
 int /*<<< orphan*/  tas_write_reg (struct tas*,int /*<<< orphan*/ ,int,unsigned char*) ; 

__attribute__((used)) static void tas3004_set_drc(struct tas *tas)
{
	unsigned char val[6];

	if (tas->drc_enabled)
		val[0] = 0x50; /* 3:1 above threshold */
	else
		val[0] = 0x51; /* disabled */
	val[1] = 0x02; /* 1:1 below threshold */
	if (tas->drc_range > 0xef)
		val[2] = 0xef;
	else if (tas->drc_range < 0)
		val[2] = 0x00;
	else
		val[2] = tas->drc_range;
	val[3] = 0xb0;
	val[4] = 0x60;
	val[5] = 0xa0;

	tas_write_reg(tas, TAS_REG_DRC, 6, val);
}