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
typedef  int /*<<< orphan*/  lithium_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ad1843_ADLEN ; 
 int /*<<< orphan*/  ad1843_ADREN ; 
 int /*<<< orphan*/  ad1843_DA1EN ; 
 int /*<<< orphan*/  ad1843_DA2EN ; 
 int /*<<< orphan*/  ad1843_DRSFLT ; 
 int /*<<< orphan*/  ad1843_write_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ad1843_write_multi (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,...) ; 
 int li_read_ad1843_reg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  li_write_ad1843_reg (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void ad1843_set_resample_mode(lithium_t *lith, int onoff)
{
	/* Save DA1 mute and gain (addr 9 is DA1 analog gain/attenuation) */
	int save_da1 = li_read_ad1843_reg(lith, 9);

	/* Power down A/D and D/A. */
	ad1843_write_multi(lith, 4,
			   &ad1843_DA1EN, 0,
			   &ad1843_DA2EN, 0,
			   &ad1843_ADLEN, 0,
			   &ad1843_ADREN, 0);

	/* Switch mode */
	ASSERT(onoff == 0 || onoff == 1);
	ad1843_write_bits(lith, &ad1843_DRSFLT, onoff);

 	/* Power up A/D and D/A. */
	ad1843_write_multi(lith, 3,
			   &ad1843_DA1EN, 1,
			   &ad1843_ADLEN, 1,
			   &ad1843_ADREN, 1);

	/* Restore DA1 mute and gain. */
	li_write_ad1843_reg(lith, 9, save_da1);
}