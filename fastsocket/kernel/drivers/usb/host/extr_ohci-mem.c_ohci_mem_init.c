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
struct td {int dummy; } ;
struct ohci_hcd {void* td_cache; void* ed_cache; } ;
struct ed {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (void*) ; 
 TYPE_2__* ohci_to_hcd (struct ohci_hcd*) ; 

__attribute__((used)) static int ohci_mem_init (struct ohci_hcd *ohci)
{
	ohci->td_cache = dma_pool_create ("ohci_td",
		ohci_to_hcd(ohci)->self.controller,
		sizeof (struct td),
		32 /* byte alignment */,
		0 /* no page-crossing issues */);
	if (!ohci->td_cache)
		return -ENOMEM;
	ohci->ed_cache = dma_pool_create ("ohci_ed",
		ohci_to_hcd(ohci)->self.controller,
		sizeof (struct ed),
		16 /* byte alignment */,
		0 /* no page-crossing issues */);
	if (!ohci->ed_cache) {
		dma_pool_destroy (ohci->td_cache);
		return -ENOMEM;
	}
	return 0;
}