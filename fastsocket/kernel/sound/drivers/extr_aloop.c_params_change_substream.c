#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct loopback_pcm {TYPE_2__* cable; TYPE_1__* substream; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */

__attribute__((used)) static void params_change_substream(struct loopback_pcm *dpcm,
				    struct snd_pcm_runtime *runtime)
{
	struct snd_pcm_runtime *dst_runtime;

	if (dpcm == NULL || dpcm->substream == NULL)
		return;
	dst_runtime = dpcm->substream->runtime;
	if (dst_runtime == NULL)
		return;
	dst_runtime->hw = dpcm->cable->hw;
}