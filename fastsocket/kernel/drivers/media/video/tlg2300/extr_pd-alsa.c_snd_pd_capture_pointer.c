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
struct poseidon_audio {int /*<<< orphan*/  rcv_position; } ;
struct poseidon {struct poseidon_audio audio; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 struct poseidon* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_pd_capture_pointer(struct snd_pcm_substream *substream)
{
	struct poseidon *p = snd_pcm_substream_chip(substream);
	struct poseidon_audio *pa = &p->audio;
	return pa->rcv_position;
}