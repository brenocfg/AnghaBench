#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_flags; int vm_start; unsigned long vm_end; } ;
struct file {struct client* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pages; } ;
struct client {int vm_start; TYPE_4__* device; TYPE_1__ buffer; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_6__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 scalar_t__ fw_device_is_shutdown (TYPE_4__*) ; 
 int /*<<< orphan*/  fw_iso_buffer_destroy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int fw_iso_buffer_init (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int fw_iso_buffer_map (TYPE_1__*,struct vm_area_struct*) ; 

__attribute__((used)) static int fw_device_op_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct client *client = file->private_data;
	enum dma_data_direction direction;
	unsigned long size;
	int page_count, ret;

	if (fw_device_is_shutdown(client->device))
		return -ENODEV;

	/* FIXME: We could support multiple buffers, but we don't. */
	if (client->buffer.pages != NULL)
		return -EBUSY;

	if (!(vma->vm_flags & VM_SHARED))
		return -EINVAL;

	if (vma->vm_start & ~PAGE_MASK)
		return -EINVAL;

	client->vm_start = vma->vm_start;
	size = vma->vm_end - vma->vm_start;
	page_count = size >> PAGE_SHIFT;
	if (size & ~PAGE_MASK)
		return -EINVAL;

	if (vma->vm_flags & VM_WRITE)
		direction = DMA_TO_DEVICE;
	else
		direction = DMA_FROM_DEVICE;

	ret = fw_iso_buffer_init(&client->buffer, client->device->card,
				 page_count, direction);
	if (ret < 0)
		return ret;

	ret = fw_iso_buffer_map(&client->buffer, vma);
	if (ret < 0)
		fw_iso_buffer_destroy(&client->buffer, client->device->card);

	return ret;
}