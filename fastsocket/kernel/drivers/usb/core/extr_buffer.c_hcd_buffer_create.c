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
struct TYPE_5__ {TYPE_3__* controller; } ;
struct usb_hcd {int /*<<< orphan*/ * pool; TYPE_2__ self; TYPE_1__* driver; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma_mask; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HCD_BUFFER_POOLS ; 
 int HCD_LOCAL_MEM ; 
 int /*<<< orphan*/  dma_pool_create (char*,TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcd_buffer_destroy (struct usb_hcd*) ; 
 int* pool_max ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int hcd_buffer_create(struct usb_hcd *hcd)
{
	char		name[16];
	int 		i, size;

	if (!hcd->self.controller->dma_mask &&
	    !(hcd->driver->flags & HCD_LOCAL_MEM))
		return 0;

	for (i = 0; i < HCD_BUFFER_POOLS; i++) {
		size = pool_max[i];
		if (!size)
			continue;
		snprintf(name, sizeof name, "buffer-%d", size);
		hcd->pool[i] = dma_pool_create(name, hcd->self.controller,
				size, size, 0);
		if (!hcd->pool [i]) {
			hcd_buffer_destroy(hcd);
			return -ENOMEM;
		}
	}
	return 0;
}