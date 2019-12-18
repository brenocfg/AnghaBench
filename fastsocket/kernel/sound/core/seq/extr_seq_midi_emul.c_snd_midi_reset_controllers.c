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
struct snd_midi_channel {int gm_volume; int gm_expression; int gm_pan; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_midi_reset_controllers(struct snd_midi_channel *chan)
{
	memset(chan->control, 0, sizeof(chan->control));
	chan->gm_volume = 127;
	chan->gm_expression = 127;
	chan->gm_pan = 64;
}