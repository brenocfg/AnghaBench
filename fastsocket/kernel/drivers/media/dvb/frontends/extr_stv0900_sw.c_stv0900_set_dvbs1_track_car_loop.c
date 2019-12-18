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
typedef  int u32 ;
struct stv0900_internal {int chip_id; } ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  ACLC ; 
 int /*<<< orphan*/  BCLC ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stv0900_set_dvbs1_track_car_loop(struct stv0900_internal *intp,
					enum fe_stv0900_demod_num demod,
					u32 srate)
{
	if (intp->chip_id >= 0x30) {
		if (srate >= 15000000) {
			stv0900_write_reg(intp, ACLC, 0x2b);
			stv0900_write_reg(intp, BCLC, 0x1a);
		} else if ((srate >= 7000000) && (15000000 > srate)) {
			stv0900_write_reg(intp, ACLC, 0x0c);
			stv0900_write_reg(intp, BCLC, 0x1b);
		} else if (srate < 7000000) {
			stv0900_write_reg(intp, ACLC, 0x2c);
			stv0900_write_reg(intp, BCLC, 0x1c);
		}

	} else { /*cut 2.0 and 1.x*/
		stv0900_write_reg(intp, ACLC, 0x1a);
		stv0900_write_reg(intp, BCLC, 0x09);
	}

}