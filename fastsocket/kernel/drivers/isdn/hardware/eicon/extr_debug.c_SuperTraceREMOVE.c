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
struct TYPE_6__ {int PLength; int /*<<< orphan*/ * P; } ;
struct TYPE_7__ {int request_pending; scalar_t__* xbuffer; TYPE_2__ XData; TYPE_1__* pIdiLib; scalar_t__ request; } ;
typedef  TYPE_3__ diva_maint_client_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_8__ {int XNum; TYPE_2__* X; scalar_t__ ReqCh; int /*<<< orphan*/  Req; } ;
struct TYPE_5__ {int /*<<< orphan*/  hLib; scalar_t__ (* DivaSTraceGetHandle ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ ENTITY ;

/* Variables and functions */
 int /*<<< orphan*/  REMOVE ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

int SuperTraceREMOVE (void* AdapterHandle) {
  diva_maint_client_t* pC = (diva_maint_client_t*)AdapterHandle;

  if (pC && pC->pIdiLib && pC->request) {
    ENTITY* e = (ENTITY*)(*(pC->pIdiLib->DivaSTraceGetHandle))(pC->pIdiLib->hLib);

    e->XNum        = 1;
    e->X           = &pC->XData;
    e->Req         = REMOVE;
    e->ReqCh       = 0;
    e->X->PLength  = 1;
    e->X->P        = (byte*)&pC->xbuffer[0];
    pC->xbuffer[0] = 0;

    pC->request_pending = 1;

    return (0);
  }

  return (-1);
}