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

/* Variables and functions */
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * snd_cx25821_cards ; 

__attribute__((used)) static void cx25821_audio_fini(void)
{
	snd_card_free(snd_cx25821_cards[0]);
}