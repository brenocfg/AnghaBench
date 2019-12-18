#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
struct TYPE_8__ {size_t length; size_t value_length; size_t type; } ;
typedef  TYPE_3__ diva_man_var_header_t ;
struct TYPE_9__ {int request_pending; int /*<<< orphan*/ * xbuffer; TYPE_1__* pIdiLib; scalar_t__ request; } ;
typedef  TYPE_4__ diva_maint_client_t ;
typedef  size_t byte ;
struct TYPE_10__ {TYPE_2__* X; scalar_t__ ReqCh; int /*<<< orphan*/  Req; } ;
struct TYPE_7__ {size_t PLength; size_t* P; } ;
struct TYPE_6__ {int /*<<< orphan*/  hLib; scalar_t__ (* DivaSTraceGetHandle ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ ENTITY ;

/* Variables and functions */
 int /*<<< orphan*/  MAN_WRITE ; 
 size_t SuperTraceCreateReadReq (size_t*,char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  single_p (size_t*,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

int SuperTraceWriteVar (void* AdapterHandle,
                        byte* data,
                        const char* name,
                        void* var,
                        byte type,
                        byte var_length) {
  diva_maint_client_t* pC = (diva_maint_client_t*)AdapterHandle;

  if (pC && pC->pIdiLib && pC->request) {
    ENTITY* e = (ENTITY*)(*(pC->pIdiLib->DivaSTraceGetHandle))(pC->pIdiLib->hLib);
    diva_man_var_header_t* pVar = (diva_man_var_header_t*)&pC->xbuffer[0];
    word length = SuperTraceCreateReadReq ((byte*)pVar, name);

    memcpy (&pC->xbuffer[length], var, var_length);
    length += var_length;
    pVar->length += var_length;
    pVar->value_length = var_length;
    pVar->type = type;
    single_p ((byte*)pVar, &length, 0); /* End Of Message */

    e->Req          = MAN_WRITE;
    e->ReqCh			  = 0;
    e->X->PLength   = length;
    e->X->P			    = (byte*)pVar;

    pC->request_pending = 1;

    return (0);
  }

  return (-1);
}