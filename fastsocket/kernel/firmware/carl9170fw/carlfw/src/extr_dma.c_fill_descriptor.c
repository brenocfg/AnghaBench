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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct dma_desc {int /*<<< orphan*/ * nextAddr; int /*<<< orphan*/ * dataAddr; struct dma_desc* lastAddr; scalar_t__ totalLen; int /*<<< orphan*/  dataSize; scalar_t__ ctrl; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_OWN_BITS_SW ; 

__attribute__((used)) static void fill_descriptor(struct dma_desc *d, uint16_t size, uint8_t *data)
{
	d->status = AR9170_OWN_BITS_SW;
	d->ctrl = 0;
	d->dataSize = size;
	d->totalLen = 0;
	d->lastAddr = d;
	d->dataAddr = data;
	d->nextAddr = NULL;
}