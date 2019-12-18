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
struct config_request {scalar_t__ sz; int /*<<< orphan*/  page_dma; int /*<<< orphan*/  page; } ;
struct MPT2SAS_ADAPTER {scalar_t__ config_page_sz; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_config_free_config_dma_memory(struct MPT2SAS_ADAPTER *ioc,
    struct config_request *mem)
{
	if (mem->sz > ioc->config_page_sz)
		dma_free_coherent(&ioc->pdev->dev, mem->sz, mem->page,
		    mem->page_dma);
}