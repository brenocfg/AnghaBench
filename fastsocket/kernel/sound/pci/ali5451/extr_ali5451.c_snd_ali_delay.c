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
struct snd_ali {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALI_STIMER ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long inl (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_ali_stimer_ready (struct snd_ali*) ; 

__attribute__((used)) static void snd_ali_delay(struct snd_ali *codec,int interval)
{
	unsigned long  begintimer,currenttimer;

	begintimer   = inl(ALI_REG(codec, ALI_STIMER));
	currenttimer = inl(ALI_REG(codec, ALI_STIMER));

	while (currenttimer < begintimer + interval) {
		if (snd_ali_stimer_ready(codec) < 0)
			break;
		currenttimer = inl(ALI_REG(codec,  ALI_STIMER));
		cpu_relax();
	}
}