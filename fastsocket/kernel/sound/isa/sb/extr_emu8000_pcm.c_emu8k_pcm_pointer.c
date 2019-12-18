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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_emu8k_pcm {scalar_t__ running; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {struct snd_emu8k_pcm* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  emu8k_get_curpos (struct snd_emu8k_pcm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t emu8k_pcm_pointer(struct snd_pcm_substream *subs)
{
	struct snd_emu8k_pcm *rec = subs->runtime->private_data;
	if (rec->running)
		return emu8k_get_curpos(rec, 0);
	return 0;
}