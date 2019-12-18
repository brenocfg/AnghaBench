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
struct vpif_fh {TYPE_1__* channel; } ;
struct vm_area_struct {int dummy; } ;
struct file {struct vpif_fh* private_data; } ;
struct common_obj {int /*<<< orphan*/  buffer_queue; } ;
struct TYPE_2__ {struct common_obj* common; } ;

/* Variables and functions */
 size_t VPIF_VIDEO_INDEX ; 
 int videobuf_mmap_mapper (int /*<<< orphan*/ *,struct vm_area_struct*) ; 

__attribute__((used)) static int vpif_mmap(struct file *filep, struct vm_area_struct *vma)
{
	struct vpif_fh *fh = filep->private_data;
	struct common_obj *common = &fh->channel->common[VPIF_VIDEO_INDEX];

	return videobuf_mmap_mapper(&common->buffer_queue, vma);
}