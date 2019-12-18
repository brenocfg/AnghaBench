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
struct snd_pcm_substream {int dummy; } ;
struct poseidon_audio {int card_close; int /*<<< orphan*/  users; } ;
struct poseidon {int /*<<< orphan*/  kref; int /*<<< orphan*/  interface; struct poseidon_audio audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poseidon_delete ; 
 struct poseidon* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_pd_pcm_close(struct snd_pcm_substream *substream)
{
	struct poseidon *p = snd_pcm_substream_chip(substream);
	struct poseidon_audio *pa = &p->audio;

	pa->users--;
	pa->card_close 		= 1;
	usb_autopm_put_interface(p->interface);
	kref_put(&p->kref, poseidon_delete);
	return 0;
}