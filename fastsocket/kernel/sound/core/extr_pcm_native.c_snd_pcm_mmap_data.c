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
struct vm_area_struct {int vm_flags; long vm_end; long vm_start; unsigned long vm_pgoff; } ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_2__* ops; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int info; scalar_t__ access; int /*<<< orphan*/  dma_bytes; TYPE_1__* status; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int (* mmap ) (struct snd_pcm_substream*,struct vm_area_struct*) ;} ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int EBADFD ; 
 int EINVAL ; 
 int ENXIO ; 
 size_t PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ SNDRV_PCM_ACCESS_RW_INTERLEAVED ; 
 scalar_t__ SNDRV_PCM_ACCESS_RW_NONINTERLEAVED ; 
 int SNDRV_PCM_INFO_MMAP ; 
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int VM_READ ; 
 int VM_WRITE ; 
 int snd_pcm_lib_default_mmap (struct snd_pcm_substream*,struct vm_area_struct*) ; 
 int stub1 (struct snd_pcm_substream*,struct vm_area_struct*) ; 

int snd_pcm_mmap_data(struct snd_pcm_substream *substream, struct file *file,
		      struct vm_area_struct *area)
{
	struct snd_pcm_runtime *runtime;
	long size;
	unsigned long offset;
	size_t dma_bytes;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		if (!(area->vm_flags & (VM_WRITE|VM_READ)))
			return -EINVAL;
	} else {
		if (!(area->vm_flags & VM_READ))
			return -EINVAL;
	}
	runtime = substream->runtime;
	if (runtime->status->state == SNDRV_PCM_STATE_OPEN)
		return -EBADFD;
	if (!(runtime->info & SNDRV_PCM_INFO_MMAP))
		return -ENXIO;
	if (runtime->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED ||
	    runtime->access == SNDRV_PCM_ACCESS_RW_NONINTERLEAVED)
		return -EINVAL;
	size = area->vm_end - area->vm_start;
	offset = area->vm_pgoff << PAGE_SHIFT;
	dma_bytes = PAGE_ALIGN(runtime->dma_bytes);
	if ((size_t)size > dma_bytes)
		return -EINVAL;
	if (offset > dma_bytes - size)
		return -EINVAL;

	if (substream->ops->mmap)
		return substream->ops->mmap(substream, area);
	else
		return snd_pcm_lib_default_mmap(substream, area);
}