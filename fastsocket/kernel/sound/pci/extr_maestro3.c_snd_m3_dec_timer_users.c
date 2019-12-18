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
struct snd_m3 {scalar_t__ timer_users; } ;

/* Variables and functions */
 int CLKRUN_GEN_ENABLE ; 
 int /*<<< orphan*/  HOST_INT_CTRL ; 
 int /*<<< orphan*/  KDATA_TIMER_COUNT_CURRENT ; 
 int /*<<< orphan*/  KDATA_TIMER_COUNT_RELOAD ; 
 int /*<<< orphan*/  MEMTYPE_INTERNAL_DATA ; 
 int /*<<< orphan*/  snd_m3_assp_write (struct snd_m3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_m3_inw (struct snd_m3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_m3_outw (struct snd_m3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_m3_dec_timer_users(struct snd_m3 *chip)
{
	chip->timer_users--;
	if (chip->timer_users > 0)  
		return;

	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_TIMER_COUNT_RELOAD,
			  0);

	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_TIMER_COUNT_CURRENT,
			  0);

	snd_m3_outw(chip,
		    snd_m3_inw(chip, HOST_INT_CTRL) & ~CLKRUN_GEN_ENABLE,
		    HOST_INT_CTRL);
}