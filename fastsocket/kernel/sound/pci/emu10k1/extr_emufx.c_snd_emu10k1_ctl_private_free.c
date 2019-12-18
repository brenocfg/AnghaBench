#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct snd_emu10k1_fx8010_ctl* p; } ;
struct snd_kcontrol {TYPE_1__ tlv; scalar_t__ private_value; } ;
struct snd_emu10k1_fx8010_ctl {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_emu10k1_fx8010_ctl*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_emu10k1_ctl_private_free(struct snd_kcontrol *kctl)
{
	struct snd_emu10k1_fx8010_ctl *ctl;
	
	ctl = (struct snd_emu10k1_fx8010_ctl *) kctl->private_value;
	kctl->private_value = 0;
	list_del(&ctl->list);
	kfree(ctl);
	if (kctl->tlv.p)
		kfree(kctl->tlv.p);
}