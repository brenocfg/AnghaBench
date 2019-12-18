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
struct vm_area_struct {int /*<<< orphan*/  vm_flags; struct snd_pcm_substream* vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct snd_pcm_substream {int /*<<< orphan*/  mmap_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_RESERVED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_vm_ops_data ; 

int snd_pcm_lib_default_mmap(struct snd_pcm_substream *substream,
			     struct vm_area_struct *area)
{
	area->vm_ops = &snd_pcm_vm_ops_data;
	area->vm_private_data = substream;
	area->vm_flags |= VM_RESERVED;
	atomic_inc(&substream->mmap_count);
	return 0;
}