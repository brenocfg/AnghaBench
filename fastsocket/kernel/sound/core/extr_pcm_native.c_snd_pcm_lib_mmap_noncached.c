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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_default_mmap (struct snd_pcm_substream*,struct vm_area_struct*) ; 

int snd_pcm_lib_mmap_noncached(struct snd_pcm_substream *substream,
			       struct vm_area_struct *area)
{
	area->vm_page_prot = pgprot_noncached(area->vm_page_prot);
	return snd_pcm_lib_default_mmap(substream, area);
}