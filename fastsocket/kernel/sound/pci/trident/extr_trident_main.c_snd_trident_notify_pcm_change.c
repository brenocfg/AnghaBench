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
struct snd_trident_pcm_mixer {int dummy; } ;
struct snd_trident {int /*<<< orphan*/  ctl_cvol; int /*<<< orphan*/  card; int /*<<< orphan*/  ctl_rvol; int /*<<< orphan*/  ctl_pan; int /*<<< orphan*/  ctl_vol; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_trident_notify_pcm_change1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void snd_trident_notify_pcm_change(struct snd_trident *trident,
					  struct snd_trident_pcm_mixer *tmix,
					  int num, int activate)
{
	snd_trident_notify_pcm_change1(trident->card, trident->ctl_vol, num, activate);
	snd_trident_notify_pcm_change1(trident->card, trident->ctl_pan, num, activate);
	snd_trident_notify_pcm_change1(trident->card, trident->ctl_rvol, num, activate);
	snd_trident_notify_pcm_change1(trident->card, trident->ctl_cvol, num, activate);
}