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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_TS_CR ; 
 int UCB_TS_CR_MODE_INT ; 
 int UCB_TS_CR_TSMX_POW ; 
 int UCB_TS_CR_TSMY_GND ; 
 int UCB_TS_CR_TSPX_POW ; 
 int UCB_TS_CR_TSPY_GND ; 
 int /*<<< orphan*/  ucb1400_reg_write (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ucb1400_ts_mode_int(struct snd_ac97 *ac97)
{
	ucb1400_reg_write(ac97, UCB_TS_CR,
			UCB_TS_CR_TSMX_POW | UCB_TS_CR_TSPX_POW |
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_GND |
			UCB_TS_CR_MODE_INT);
}