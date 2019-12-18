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
 unsigned short UCB_TS_CR_TSMX_LOW ; 
 unsigned short UCB_TS_CR_TSPX_LOW ; 
 unsigned short ucb1400_reg_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ucb1400_ts_pen_up(struct snd_ac97 *ac97)
{
	unsigned short val = ucb1400_reg_read(ac97, UCB_TS_CR);

	return val & (UCB_TS_CR_TSPX_LOW | UCB_TS_CR_TSMX_LOW);
}