#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dword ;
struct TYPE_6__ {scalar_t__ serial; int /*<<< orphan*/  Rc; scalar_t__ Req; } ;
struct TYPE_5__ {scalar_t__ logical_adapter_number; } ;
struct TYPE_7__ {TYPE_1__ info; int /*<<< orphan*/  Rc; scalar_t__ Req; } ;
struct TYPE_8__ {TYPE_2__ GetSerial; TYPE_3__ xdi_logical_adapter_number; } ;
typedef  TYPE_4__ IDI_SYNC_REQ ;
typedef  int /*<<< orphan*/  (* IDI_CALL ) (int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  ENTITY ;

/* Variables and functions */
 int /*<<< orphan*/  IDI_SYNC_REQ_GET_SERIAL ; 
 int /*<<< orphan*/  IDI_SYNC_REQ_XDI_GET_LOGICAL_ADAPTER_NUMBER ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int diva_get_idi_adapter_info (IDI_CALL request, dword* serial, dword* logical) {
  IDI_SYNC_REQ sync_req;

  sync_req.xdi_logical_adapter_number.Req = 0;
  sync_req.xdi_logical_adapter_number.Rc = IDI_SYNC_REQ_XDI_GET_LOGICAL_ADAPTER_NUMBER;
  (*request)((ENTITY *)&sync_req);
  *logical = sync_req.xdi_logical_adapter_number.info.logical_adapter_number;

  sync_req.GetSerial.Req = 0;
  sync_req.GetSerial.Rc = IDI_SYNC_REQ_GET_SERIAL;
  sync_req.GetSerial.serial = 0;
  (*request)((ENTITY *)&sync_req);
	*serial = sync_req.GetSerial.serial;

  return (0);
}