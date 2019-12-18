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
struct tas {int /*<<< orphan*/  treble; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAS_REG_TREBLE ; 
 int /*<<< orphan*/  tas3004_treble (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tas_write_reg (struct tas*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tas_set_treble(struct tas *tas)
{
	u8 tmp;

	tmp = tas3004_treble(tas->treble);
	tas_write_reg(tas, TAS_REG_TREBLE, 1, &tmp);
}