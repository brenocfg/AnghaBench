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
struct tty_struct {struct snd_soc_codec* disc_data; } ;
struct snd_soc_codec {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pins; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* close ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__ ams_delta_hook_switch ; 
 int /*<<< orphan*/  cx81801_timer ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 TYPE_1__ v253_ops ; 

__attribute__((used)) static void cx81801_close(struct tty_struct *tty)
{
	struct snd_soc_codec *codec = tty->disc_data;

	del_timer_sync(&cx81801_timer);

	v253_ops.close(tty);

	/* Prevent the hook switch from further changing the DAPM pins */
	INIT_LIST_HEAD(&ams_delta_hook_switch.pins);

	/* Revert back to default audio input/output constellation */
	snd_soc_dapm_disable_pin(codec, "Mouthpiece");
	snd_soc_dapm_enable_pin(codec, "Earpiece");
	snd_soc_dapm_enable_pin(codec, "Microphone");
	snd_soc_dapm_disable_pin(codec, "Speaker");
	snd_soc_dapm_disable_pin(codec, "AGCIN");
	snd_soc_dapm_sync(codec);
}