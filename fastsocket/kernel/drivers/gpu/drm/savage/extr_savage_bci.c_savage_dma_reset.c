#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {unsigned int event_wrap; unsigned int nr_dma_pages; scalar_t__ current_dma_page; scalar_t__ first_dma_page; int /*<<< orphan*/  last_dma_age; TYPE_1__* dma_pages; } ;
typedef  TYPE_2__ drm_savage_private_t ;
struct TYPE_5__ {scalar_t__ flushed; scalar_t__ used; int /*<<< orphan*/  age; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_AGE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  savage_bci_emit_event (TYPE_2__*,int /*<<< orphan*/ ) ; 

void savage_dma_reset(drm_savage_private_t * dev_priv)
{
	uint16_t event;
	unsigned int wrap, i;
	event = savage_bci_emit_event(dev_priv, 0);
	wrap = dev_priv->event_wrap;
	for (i = 0; i < dev_priv->nr_dma_pages; ++i) {
		SET_AGE(&dev_priv->dma_pages[i].age, event, wrap);
		dev_priv->dma_pages[i].used = 0;
		dev_priv->dma_pages[i].flushed = 0;
	}
	SET_AGE(&dev_priv->last_dma_age, event, wrap);
	dev_priv->first_dma_page = dev_priv->current_dma_page = 0;
}