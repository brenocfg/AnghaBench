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
struct poseidon_audio {scalar_t__ card; } ;
struct poseidon {struct poseidon_audio audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_free (scalar_t__) ; 

int poseidon_audio_free(struct poseidon *p)
{
	struct poseidon_audio *pa = &p->audio;

	if (pa->card)
		snd_card_free(pa->card);
	return 0;
}