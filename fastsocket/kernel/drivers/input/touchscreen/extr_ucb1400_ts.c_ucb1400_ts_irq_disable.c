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
 int /*<<< orphan*/  UCB_IE_FAL ; 
 int /*<<< orphan*/  ucb1400_reg_write (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ucb1400_ts_irq_disable(struct snd_ac97 *ac97)
{
	ucb1400_reg_write(ac97, UCB_IE_FAL, 0);
}