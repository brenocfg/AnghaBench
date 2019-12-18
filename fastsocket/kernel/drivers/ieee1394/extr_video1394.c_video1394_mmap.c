#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct file_ctx {TYPE_3__* current_ctx; TYPE_2__* ohci; } ;
struct file {scalar_t__ private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma; } ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int dma_region_mmap (int /*<<< orphan*/ *,struct file*,struct vm_area_struct*) ; 

__attribute__((used)) static int video1394_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct file_ctx *ctx = (struct file_ctx *)file->private_data;

	if (ctx->current_ctx == NULL) {
		PRINT(KERN_ERR, ctx->ohci->host->id,
				"Current iso context not set");
		return -EINVAL;
	}

	return dma_region_mmap(&ctx->current_ctx->dma, file, vma);
}