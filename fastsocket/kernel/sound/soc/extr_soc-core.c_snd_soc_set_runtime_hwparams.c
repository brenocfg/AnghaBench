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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  fifo_size; int /*<<< orphan*/  buffer_bytes_max; int /*<<< orphan*/  periods_max; int /*<<< orphan*/  periods_min; int /*<<< orphan*/  period_bytes_max; int /*<<< orphan*/  period_bytes_min; int /*<<< orphan*/  formats; int /*<<< orphan*/  info; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct snd_pcm_hardware {int /*<<< orphan*/  fifo_size; int /*<<< orphan*/  buffer_bytes_max; int /*<<< orphan*/  periods_max; int /*<<< orphan*/  periods_min; int /*<<< orphan*/  period_bytes_max; int /*<<< orphan*/  period_bytes_min; int /*<<< orphan*/  formats; int /*<<< orphan*/  info; } ;

/* Variables and functions */

int snd_soc_set_runtime_hwparams(struct snd_pcm_substream *substream,
	const struct snd_pcm_hardware *hw)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	runtime->hw.info = hw->info;
	runtime->hw.formats = hw->formats;
	runtime->hw.period_bytes_min = hw->period_bytes_min;
	runtime->hw.period_bytes_max = hw->period_bytes_max;
	runtime->hw.periods_min = hw->periods_min;
	runtime->hw.periods_max = hw->periods_max;
	runtime->hw.buffer_bytes_max = hw->buffer_bytes_max;
	runtime->hw.fifo_size = hw->fifo_size;
	return 0;
}