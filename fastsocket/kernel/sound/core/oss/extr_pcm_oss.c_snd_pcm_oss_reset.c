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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct TYPE_2__ {int prepare; scalar_t__ period_ptr; scalar_t__ prev_hw_ptr_period; scalar_t__ buffer_used; } ;
struct snd_pcm_runtime2 {TYPE_1__ oss; } ;
struct snd_pcm_oss_file {struct snd_pcm_substream** streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_DROP ; 
 struct snd_pcm_runtime2* oss_runtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_kernel_ioctl (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_oss_reset(struct snd_pcm_oss_file *pcm_oss_file)
{
	struct snd_pcm_substream *substream;
	struct snd_pcm_runtime2 *runtime;
	int i;

	for (i = 0; i < 2; i++) { 
		substream = pcm_oss_file->streams[i];
		if (!substream)
			continue;
		runtime = oss_runtime(substream->runtime);
		snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DROP, NULL);
		runtime->oss.prepare = 1;
		runtime->oss.buffer_used = 0;
		runtime->oss.prev_hw_ptr_period = 0;
		runtime->oss.period_ptr = 0;
	}
	return 0;
}