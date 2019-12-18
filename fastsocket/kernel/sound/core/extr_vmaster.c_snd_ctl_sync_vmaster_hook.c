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
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ctl_sync_vmaster (struct snd_kcontrol*,int) ; 

void snd_ctl_sync_vmaster_hook(struct snd_kcontrol *kcontrol)
{
	snd_ctl_sync_vmaster(kcontrol, true);
}