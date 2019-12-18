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
struct frame {int /*<<< orphan*/  descriptor_pool_dma; int /*<<< orphan*/  descriptor_pool; int /*<<< orphan*/  descriptor_pool_size; TYPE_2__* video; int /*<<< orphan*/  header_pool_dma; int /*<<< orphan*/  header_pool; } ;
struct TYPE_4__ {TYPE_1__* ohci; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (struct frame*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void frame_delete(struct frame *f)
{
	pci_free_consistent(f->video->ohci->dev, PAGE_SIZE, f->header_pool, f->header_pool_dma);
	pci_free_consistent(f->video->ohci->dev, f->descriptor_pool_size, f->descriptor_pool, f->descriptor_pool_dma);
	kfree(f);
}