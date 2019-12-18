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
struct tty_struct {struct snd_soc_codec* disc_data; } ;
struct snd_soc_codec {scalar_t__ pop_time; int /*<<< orphan*/ * control_data; int /*<<< orphan*/ * hw_write; } ;

/* Variables and functions */

__attribute__((used)) static void v253_close(struct tty_struct *tty)
{
	struct snd_soc_codec *codec = tty->disc_data;

	tty->disc_data = NULL;

	if (!codec)
		return;

	/* Prevent the codec driver from further accessing the modem */
	codec->hw_write = NULL;
	codec->control_data = NULL;
	codec->pop_time = 0;
}