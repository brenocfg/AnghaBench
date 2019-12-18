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
struct TYPE_3__ {int /*<<< orphan*/  stop; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;
struct snd_ali {TYPE_2__ chregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_printk (char*,unsigned int) ; 

__attribute__((used)) static void snd_ali_stop_voice(struct snd_ali *codec, unsigned int channel)
{
	unsigned int mask = 1 << (channel & 0x1f);

	snd_ali_printk("stop_voice: channel=%d\n",channel);
	outl(mask, ALI_REG(codec, codec->chregs.regs.stop));
}