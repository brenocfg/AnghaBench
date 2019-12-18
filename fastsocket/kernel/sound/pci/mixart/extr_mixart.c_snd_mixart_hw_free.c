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
struct snd_mixart {int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mixart_sync_nonblock_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_mixart* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_mixart_hw_free(struct snd_pcm_substream *subs)
{
	struct snd_mixart *chip = snd_pcm_substream_chip(subs);
	snd_pcm_lib_free_pages(subs);
	mixart_sync_nonblock_events(chip->mgr);
	return 0;
}