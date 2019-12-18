#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct mi_pc_maint {int dummy; } ;
struct TYPE_11__ {int data_length; int /*<<< orphan*/  status; TYPE_3__* data; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* DIRequest ) (TYPE_5__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  Initialized; } ;
struct TYPE_12__ {TYPE_1__ xdi_mbox; TYPE_5__ xdi_adapter; } ;
typedef  TYPE_2__ diva_os_xdi_adapter_t ;
struct TYPE_13__ {int command; int rc; int /*<<< orphan*/  req; } ;
typedef  TYPE_3__ diva_get_xlog_t ;
typedef  TYPE_3__ byte ;
typedef  int /*<<< orphan*/  ENTITY ;

/* Variables and functions */
 int /*<<< orphan*/  DIVA_XDI_MBOX_BUSY ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  diva_os_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* diva_os_malloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *) ; 

int diva_card_read_xlog(diva_os_xdi_adapter_t * a)
{
	diva_get_xlog_t *req;
	byte *data;

	if (!a->xdi_adapter.Initialized || !a->xdi_adapter.DIRequest) {
		return (-1);
	}
	if (!(data = diva_os_malloc(0, sizeof(struct mi_pc_maint)))) {
		return (-1);
	}
	memset(data, 0x00, sizeof(struct mi_pc_maint));

	if (!(req = diva_os_malloc(0, sizeof(*req)))) {
		diva_os_free(0, data);
		return (-1);
	}
	req->command = 0x0400;
	req->req = LOG;
	req->rc = 0x00;

	(*(a->xdi_adapter.DIRequest)) (&a->xdi_adapter, (ENTITY *) req);

	if (!req->rc || req->req) {
		diva_os_free(0, data);
		diva_os_free(0, req);
		return (-1);
	}

	memcpy(data, &req->req, sizeof(struct mi_pc_maint));

	diva_os_free(0, req);

	a->xdi_mbox.data_length = sizeof(struct mi_pc_maint);
	a->xdi_mbox.data = data;
	a->xdi_mbox.status = DIVA_XDI_MBOX_BUSY;

	return (0);
}