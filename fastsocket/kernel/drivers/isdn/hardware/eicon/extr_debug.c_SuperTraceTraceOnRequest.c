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
typedef  int /*<<< orphan*/  word ;
struct TYPE_7__ {int request_pending; int /*<<< orphan*/ * xbuffer; TYPE_1__* pIdiLib; scalar_t__ request; } ;
typedef  TYPE_3__ diva_maint_client_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_8__ {TYPE_2__* X; scalar_t__ ReqCh; int /*<<< orphan*/  Req; } ;
struct TYPE_6__ {int /*<<< orphan*/ * P; int /*<<< orphan*/  PLength; } ;
struct TYPE_5__ {int /*<<< orphan*/  hLib; scalar_t__ (* DivaSTraceGetHandle ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ ENTITY ;

/* Variables and functions */
 int /*<<< orphan*/  MAN_EVENT_ON ; 
 int /*<<< orphan*/  SuperTraceCreateReadReq (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  single_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

int SuperTraceTraceOnRequest(void* hAdapter, const char* name, byte* data) {
  diva_maint_client_t* pC = (diva_maint_client_t*)hAdapter;

  if (pC && pC->pIdiLib && pC->request) {
    ENTITY* e = (ENTITY*)(*(pC->pIdiLib->DivaSTraceGetHandle))(pC->pIdiLib->hLib);
    byte* xdata = (byte*)&pC->xbuffer[0];
    char tmp = 0;
    word length;

    if (!strcmp(name, "\\")) { /* Read ROOT */
      name = &tmp;
    }
    length = SuperTraceCreateReadReq (xdata, name);
    single_p (xdata, &length, 0); /* End Of Message */
    e->Req          = MAN_EVENT_ON;
    e->ReqCh        = 0;
    e->X->PLength   = length;
    e->X->P			    = (byte*)xdata;

    pC->request_pending = 1;

    return (0);
  }

  return (-1);
}