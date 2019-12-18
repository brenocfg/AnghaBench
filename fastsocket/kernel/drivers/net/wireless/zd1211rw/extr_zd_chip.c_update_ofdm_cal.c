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
typedef  int u8 ;
struct zd_ioreq16 {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;
struct zd_chip {int /*<<< orphan*/ ** ofdm_cal_values; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16*) ; 
 size_t OFDM_36M_INDEX ; 
 size_t OFDM_48M_INDEX ; 
 size_t OFDM_54M_INDEX ; 
 int /*<<< orphan*/  ZD_CR65 ; 
 int /*<<< orphan*/  ZD_CR66 ; 
 int /*<<< orphan*/  ZD_CR67 ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_ofdm_cal(struct zd_chip *chip, u8 channel)
{
	struct zd_ioreq16 ioreqs[3];

	ioreqs[0].addr = ZD_CR67;
	ioreqs[0].value = chip->ofdm_cal_values[OFDM_36M_INDEX][channel-1];
	ioreqs[1].addr = ZD_CR66;
	ioreqs[1].value = chip->ofdm_cal_values[OFDM_48M_INDEX][channel-1];
	ioreqs[2].addr = ZD_CR65;
	ioreqs[2].value = chip->ofdm_cal_values[OFDM_54M_INDEX][channel-1];

	return zd_iowrite16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
}