#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  done; } ;
typedef  TYPE_1__ hfa384x_usbctlx_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static hfa384x_usbctlx_t *usbctlx_alloc(void)
{
	hfa384x_usbctlx_t *ctlx;

	ctlx = kmalloc(sizeof(*ctlx), in_interrupt()? GFP_ATOMIC : GFP_KERNEL);
	if (ctlx != NULL) {
		memset(ctlx, 0, sizeof(*ctlx));
		init_completion(&ctlx->done);
	}

	return ctlx;
}