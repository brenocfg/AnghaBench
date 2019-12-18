#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ word ;
typedef  int dword ;
struct TYPE_16__ {int XNum; int RNum; int Rc; int /*<<< orphan*/ * R; TYPE_3__* X; int /*<<< orphan*/ * callback; scalar_t__ IndCh; scalar_t__ Ind; scalar_t__ RcCh; scalar_t__ ReqCh; scalar_t__ Id; scalar_t__ Req; } ;
struct TYPE_13__ {scalar_t__* P; scalar_t__ PLength; } ;
struct TYPE_14__ {int /*<<< orphan*/  status; TYPE_7__ e; TYPE_2__* adapter; int /*<<< orphan*/  rc_count; int /*<<< orphan*/  RData; TYPE_3__ XData; } ;
typedef  TYPE_4__ divas_um_idi_entity_t ;
struct TYPE_15__ {int type; scalar_t__ data_length; scalar_t__ ReqCh; scalar_t__ Req; } ;
typedef  TYPE_5__ diva_um_idi_req_hdr_t ;
typedef  scalar_t__ byte ;
struct TYPE_11__ {int /*<<< orphan*/  (* request ) (TYPE_7__*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  adapter_nr; TYPE_1__ d; } ;

/* Variables and functions */
 scalar_t__ ASSIGN ; 
 int ASSIGN_RC ; 
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_TRC (char*) ; 
 int /*<<< orphan*/  DIVA_UM_IDI_ASSIGN_PENDING ; 
 int /*<<< orphan*/  DIVA_UM_IDI_RC_PENDING ; 
#define  DIVA_UM_IDI_REQ_TYPE_MAN 130 
 int DIVA_UM_IDI_REQ_TYPE_MASK ; 
#define  DIVA_UM_IDI_REQ_TYPE_NET 129 
#define  DIVA_UM_IDI_REQ_TYPE_SIG 128 
 scalar_t__ DSIG_ID ; 
 scalar_t__ MAN_ID ; 
 scalar_t__ NL_ID ; 
 int OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  diva_um_idi_start_wdog (TYPE_4__*) ; 
 int /*<<< orphan*/ * diva_um_idi_xdi_callback ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/  write_return_code (TYPE_4__*,int) ; 

__attribute__((used)) static int process_idi_request(divas_um_idi_entity_t * e,
			       const diva_um_idi_req_hdr_t * req)
{
	int assign = 0;
	byte Req = (byte) req->Req;
	dword type = req->type & DIVA_UM_IDI_REQ_TYPE_MASK;

	if (!e->e.Id || !e->e.callback) {	/* not assigned */
		if (Req != ASSIGN) {
			DBG_ERR(("A: A(%d) E(%08x) not assigned",
				 e->adapter->adapter_nr, e));
			return (-1);	/* NOT ASSIGNED */
		} else {
			switch (type) {
			case DIVA_UM_IDI_REQ_TYPE_MAN:
				e->e.Id = MAN_ID;
				DBG_TRC(("A(%d) E(%08x) assign MAN",
					 e->adapter->adapter_nr, e));
				break;

			case DIVA_UM_IDI_REQ_TYPE_SIG:
				e->e.Id = DSIG_ID;
				DBG_TRC(("A(%d) E(%08x) assign SIG",
					 e->adapter->adapter_nr, e));
				break;

			case DIVA_UM_IDI_REQ_TYPE_NET:
				e->e.Id = NL_ID;
				DBG_TRC(("A(%d) E(%08x) assign NET",
					 e->adapter->adapter_nr, e));
				break;

			default:
				DBG_ERR(("A: A(%d) E(%08x) unknown type=%08x",
					 e->adapter->adapter_nr, e,
					 type));
				return (-1);
			}
		}
		e->e.XNum = 1;
		e->e.RNum = 1;
		e->e.callback = diva_um_idi_xdi_callback;
		e->e.X = &e->XData;
		e->e.R = &e->RData;
		assign = 1;
	}
	e->status |= DIVA_UM_IDI_RC_PENDING;
	e->e.Req = Req;
	e->e.ReqCh = (byte) req->ReqCh;
	e->e.X->PLength = (word) req->data_length;
	e->e.X->P = (byte *) & req[1];	/* Our buffer is safe */

	DBG_TRC(("A(%d) E(%08x) request(%02x-%02x-%02x (%d))",
		 e->adapter->adapter_nr, e, e->e.Id, e->e.Req,
		 e->e.ReqCh, e->e.X->PLength));

	e->rc_count++;

	if (e->adapter && e->adapter->d.request) {
		diva_um_idi_start_wdog(e);
		(*(e->adapter->d.request)) (&e->e);
	}

	if (assign) {
		if (e->e.Rc == OUT_OF_RESOURCES) {
			/*
			   XDI has no entities more, call was not forwarded to the card,
			   no callback will be scheduled
			 */
			DBG_ERR(("A: A(%d) E(%08x) XDI out of entities",
				 e->adapter->adapter_nr, e));

			e->e.Id = 0;
			e->e.ReqCh = 0;
			e->e.RcCh = 0;
			e->e.Ind = 0;
			e->e.IndCh = 0;
			e->e.XNum = 0;
			e->e.RNum = 0;
			e->e.callback = NULL;
			e->e.X = NULL;
			e->e.R = NULL;
			write_return_code(e, ASSIGN_RC | OUT_OF_RESOURCES);
			return (-2);
		} else {
			e->status |= DIVA_UM_IDI_ASSIGN_PENDING;
		}
	}

	return (0);
}