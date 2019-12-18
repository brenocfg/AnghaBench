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
struct TYPE_3__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ xdi_mbox; } ;
typedef  TYPE_2__ diva_os_xdi_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIVA_XDI_MBOX_BUSY ; 
 int /*<<< orphan*/  diva_os_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void diva_xdi_close_adapter(void *adapter, void *os_handle)
{
	diva_os_xdi_adapter_t *a = (diva_os_xdi_adapter_t *) adapter;

	a->xdi_mbox.status &= ~DIVA_XDI_MBOX_BUSY;
	if (a->xdi_mbox.data) {
		diva_os_free(0, a->xdi_mbox.data);
		a->xdi_mbox.data = NULL;
	}
}