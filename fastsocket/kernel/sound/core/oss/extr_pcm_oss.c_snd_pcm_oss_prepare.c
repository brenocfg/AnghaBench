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
struct TYPE_2__ {scalar_t__ buffer_used; scalar_t__ period_ptr; scalar_t__ prev_hw_ptr_period; scalar_t__ prepare; } ;
struct snd_pcm_runtime2 {TYPE_1__ oss; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_PREPARE ; 
 struct snd_pcm_runtime2* oss_runtime (int /*<<< orphan*/ ) ; 
 int snd_pcm_kernel_ioctl (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 

__attribute__((used)) static int snd_pcm_oss_prepare(struct snd_pcm_substream *substream)
{
	int err;
	struct snd_pcm_runtime2 *runtime = oss_runtime(substream->runtime);

	err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_PREPARE, NULL);
	if (err < 0) {
		snd_printd("snd_pcm_oss_prepare: SNDRV_PCM_IOCTL_PREPARE failed\n");
		return err;
	}
	runtime->oss.prepare = 0;
	runtime->oss.prev_hw_ptr_period = 0;
	runtime->oss.period_ptr = 0;
	runtime->oss.buffer_used = 0;

	return 0;
}