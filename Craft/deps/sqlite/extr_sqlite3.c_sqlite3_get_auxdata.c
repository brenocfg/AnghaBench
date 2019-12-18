#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* db; } ;
struct TYPE_10__ {TYPE_5__* pVdbeFunc; TYPE_2__ s; } ;
typedef  TYPE_4__ sqlite3_context ;
struct TYPE_11__ {int nAux; TYPE_3__* apAux; } ;
typedef  TYPE_5__ VdbeFunc ;
struct TYPE_9__ {void* pAux; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void *sqlite3_get_auxdata(sqlite3_context *pCtx, int iArg){
  VdbeFunc *pVdbeFunc;

  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
  pVdbeFunc = pCtx->pVdbeFunc;
  if( !pVdbeFunc || iArg>=pVdbeFunc->nAux || iArg<0 ){
    return 0;
  }
  return pVdbeFunc->apAux[iArg].pAux;
}