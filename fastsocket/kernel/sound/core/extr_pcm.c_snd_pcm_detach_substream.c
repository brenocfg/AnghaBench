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
struct snd_pcm_substream {TYPE_2__* pstr; struct snd_pcm_runtime* runtime; } ;
struct TYPE_3__ {struct snd_pcm_runtime* rules; } ;
struct snd_pcm_runtime {struct snd_pcm_runtime* hwptr_log; TYPE_1__ hw_constraints; scalar_t__ control; scalar_t__ status; int /*<<< orphan*/  (* private_free ) (struct snd_pcm_runtime*) ;} ;
struct snd_pcm_mmap_status {int dummy; } ;
struct snd_pcm_mmap_control {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  substream_opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (int) ; 
 scalar_t__ PCM_RUNTIME_CHECK (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  kfree (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_free_pages (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_runtime*) ; 

void snd_pcm_detach_substream(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime;

	if (PCM_RUNTIME_CHECK(substream))
		return;
	runtime = substream->runtime;
	if (runtime->private_free != NULL)
		runtime->private_free(runtime);
	snd_free_pages((void*)runtime->status,
		       PAGE_ALIGN(sizeof(struct snd_pcm_mmap_status)));
	snd_free_pages((void*)runtime->control,
		       PAGE_ALIGN(sizeof(struct snd_pcm_mmap_control)));
	kfree(runtime->hw_constraints.rules);
#ifdef CONFIG_SND_PCM_XRUN_DEBUG
	if (runtime->hwptr_log)
		kfree(runtime->hwptr_log);
#endif
	kfree(runtime);
	substream->runtime = NULL;
	substream->pstr->substream_opened--;
}