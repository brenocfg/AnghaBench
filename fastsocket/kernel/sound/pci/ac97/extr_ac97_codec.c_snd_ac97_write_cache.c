#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_ac97 {unsigned short* regs; int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/  reg_accessed; TYPE_2__* bus; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write ) (struct snd_ac97*,unsigned short,unsigned short) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_valid_reg (struct snd_ac97*,unsigned short) ; 
 int /*<<< orphan*/  stub1 (struct snd_ac97*,unsigned short,unsigned short) ; 

void snd_ac97_write_cache(struct snd_ac97 *ac97, unsigned short reg, unsigned short value)
{
	if (!snd_ac97_valid_reg(ac97, reg))
		return;
	mutex_lock(&ac97->reg_mutex);
	ac97->regs[reg] = value;
	ac97->bus->ops->write(ac97, reg, value);
	set_bit(reg, ac97->reg_accessed);
	mutex_unlock(&ac97->reg_mutex);
}