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
struct snd_opl4 {int /*<<< orphan*/  chset; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_midi_channel_free_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_opl4_seq_free_port(void *private_data)
{
	struct snd_opl4 *opl4 = private_data;

	snd_midi_channel_free_set(opl4->chset);
}