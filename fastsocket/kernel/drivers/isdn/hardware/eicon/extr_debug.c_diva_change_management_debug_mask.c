#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int dword ;
struct TYPE_9__ {int channels; TYPE_3__* pIdiLib; TYPE_1__* hDbg; scalar_t__ request; } ;
typedef  TYPE_2__ diva_maint_client_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* DivaSTraceSetAudioTap ) (TYPE_3__*,int,int) ;int /*<<< orphan*/  (* DivaSTraceSetBChannel ) (TYPE_3__*,int,int) ;int /*<<< orphan*/  (* DivaSTraceSetDChannel ) (TYPE_3__*,int) ;int /*<<< orphan*/  (* DivaSTraceSetInfo ) (TYPE_3__*,int) ;} ;
struct TYPE_8__ {int dbgMask; } ;

/* Variables and functions */
 int DIVA_MGT_DBG_DCHAN ; 
 int DIVA_MGT_DBG_IFC_AUDIO ; 
 int DIVA_MGT_DBG_IFC_BCHANNEL ; 
 int DIVA_MGT_DBG_TRACE ; 
 int /*<<< orphan*/ * TraceFilter ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int,int) ; 

__attribute__((used)) static void diva_change_management_debug_mask (diva_maint_client_t* pC, dword old_mask) {
  if (pC->request && pC->hDbg && pC->pIdiLib) {
    dword changed = pC->hDbg->dbgMask ^ old_mask;

    if (changed & DIVA_MGT_DBG_TRACE) {
      (*(pC->pIdiLib->DivaSTraceSetInfo))(pC->pIdiLib,
                                          (pC->hDbg->dbgMask & DIVA_MGT_DBG_TRACE) != 0);
    }
    if (changed & DIVA_MGT_DBG_DCHAN) {
      (*(pC->pIdiLib->DivaSTraceSetDChannel))(pC->pIdiLib,
                                              (pC->hDbg->dbgMask & DIVA_MGT_DBG_DCHAN) != 0);
    }
    if (!TraceFilter[0]) {
      if (changed & DIVA_MGT_DBG_IFC_BCHANNEL) {
        int i, state = ((pC->hDbg->dbgMask & DIVA_MGT_DBG_IFC_BCHANNEL) != 0);

        for (i = 0; i < pC->channels; i++) {
          (*(pC->pIdiLib->DivaSTraceSetBChannel))(pC->pIdiLib, i+1, state);
        }
      }
      if (changed & DIVA_MGT_DBG_IFC_AUDIO) {
        int i, state = ((pC->hDbg->dbgMask & DIVA_MGT_DBG_IFC_AUDIO) != 0);

        for (i = 0; i < pC->channels; i++) {
          (*(pC->pIdiLib->DivaSTraceSetAudioTap))(pC->pIdiLib, i+1, state);
        }
      }
    }
  }
}