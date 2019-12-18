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
struct tty_struct {TYPE_1__* ops; struct snd_soc_codec* disc_data; } ;
struct snd_soc_codec {int pop_time; scalar_t__ hw_write; struct tty_struct* control_data; } ;
typedef  scalar_t__ hw_write_t ;
struct TYPE_2__ {scalar_t__ write; } ;

/* Variables and functions */

__attribute__((used)) static void v253_receive(struct tty_struct *tty,
				const unsigned char *cp, char *fp, int count)
{
	struct snd_soc_codec *codec = tty->disc_data;

	if (!codec)
		return;

	if (!codec->control_data) {
		/* First modem response, complete setup procedure */

		/* Set up codec driver access to modem controls */
		codec->control_data = tty;
		codec->hw_write = (hw_write_t)tty->ops->write;
		codec->pop_time = 1;
	}
}