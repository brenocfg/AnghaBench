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
struct snd_pcm_runtime {int /*<<< orphan*/  dma_bytes; } ;
struct ct_vm {int /*<<< orphan*/  (* map ) (struct ct_vm*,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct ct_atc_pcm {int /*<<< orphan*/  vm_block; TYPE_1__* substream; } ;
struct ct_atc {struct ct_vm* vm; } ;
struct TYPE_2__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  stub1 (struct ct_vm*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ct_map_audio_buffer(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	struct snd_pcm_runtime *runtime;
	struct ct_vm *vm;

	if (!apcm->substream)
		return 0;

	runtime = apcm->substream->runtime;
	vm = atc->vm;

	apcm->vm_block = vm->map(vm, apcm->substream, runtime->dma_bytes);

	if (!apcm->vm_block)
		return -ENOENT;

	return 0;
}