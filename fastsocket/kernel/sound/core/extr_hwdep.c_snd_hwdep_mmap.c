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
struct vm_area_struct {int dummy; } ;
struct TYPE_2__ {int (* mmap ) (struct snd_hwdep*,struct file*,struct vm_area_struct*) ;} ;
struct snd_hwdep {TYPE_1__ ops; } ;
struct file {struct snd_hwdep* private_data; } ;

/* Variables and functions */
 int ENXIO ; 
 int stub1 (struct snd_hwdep*,struct file*,struct vm_area_struct*) ; 

__attribute__((used)) static int snd_hwdep_mmap(struct file * file, struct vm_area_struct * vma)
{
	struct snd_hwdep *hw = file->private_data;
	if (hw->ops.mmap)
		return hw->ops.mmap(hw, file, vma);
	return -ENXIO;
}