#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ fromMemPool; } ;
struct TYPE_7__ {int /*<<< orphan*/  pContextPool; } ;
typedef  TYPE_1__ HttpServer ;
typedef  TYPE_2__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  httpTrace (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  taosMemPoolFree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tfree (TYPE_2__*) ; 

void httpFreeContext(HttpServer *pServer, HttpContext *pContext) {
  if (pContext->fromMemPool) {
    httpTrace("context:%p, is freed from mempool", pContext);
    taosMemPoolFree(pServer->pContextPool, (char *)pContext);
  } else {
    httpTrace("context:%p, is freed from raw memory", pContext);
    tfree(pContext);
  }
}