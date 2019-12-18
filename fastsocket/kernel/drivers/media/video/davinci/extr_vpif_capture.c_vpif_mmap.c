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
struct vpif_fh {struct channel_obj* channel; } ;
struct vm_area_struct {int dummy; } ;
struct file {struct vpif_fh* private_data; } ;
struct common_obj {int /*<<< orphan*/  buffer_queue; } ;
struct channel_obj {struct common_obj* common; } ;

/* Variables and functions */
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 int videobuf_mmap_mapper (int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vpif_mmap(struct file *filep, struct vm_area_struct *vma)
{
	/* Get the channel object and file handle object */
	struct vpif_fh *fh = filep->private_data;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common = &(ch->common[VPIF_VIDEO_INDEX]);

	vpif_dbg(2, debug, "vpif_mmap\n");

	return videobuf_mmap_mapper(&common->buffer_queue, vma);
}