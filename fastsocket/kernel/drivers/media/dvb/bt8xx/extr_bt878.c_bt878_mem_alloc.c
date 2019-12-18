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
struct bt878 {int buf_size; int risc_size; void* risc_cpu; int /*<<< orphan*/  risc_dma; int /*<<< orphan*/  dev; void* buf_cpu; int /*<<< orphan*/  buf_dma; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bt878_mem_free (struct bt878*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bt878_mem_alloc(struct bt878 *bt)
{
	if (!bt->buf_cpu) {
		bt->buf_size = 128 * 1024;

		bt->buf_cpu =
		    pci_alloc_consistent(bt->dev, bt->buf_size,
					 &bt->buf_dma);

		if (!bt->buf_cpu)
			return -ENOMEM;

		memset(bt->buf_cpu, 0, bt->buf_size);
	}

	if (!bt->risc_cpu) {
		bt->risc_size = PAGE_SIZE;
		bt->risc_cpu =
		    pci_alloc_consistent(bt->dev, bt->risc_size,
					 &bt->risc_dma);

		if (!bt->risc_cpu) {
			bt878_mem_free(bt);
			return -ENOMEM;
		}

		memset(bt->risc_cpu, 0, bt->risc_size);
	}

	return 0;
}