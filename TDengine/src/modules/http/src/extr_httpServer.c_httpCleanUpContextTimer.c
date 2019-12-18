#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * timer; int /*<<< orphan*/  ipstr; } ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  httpTrace (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosTmrStopA (int /*<<< orphan*/ **) ; 

void httpCleanUpContextTimer(HttpContext *pContext) {
  if (pContext->timer != NULL) {
    taosTmrStopA(&pContext->timer);
    httpTrace("context:%p, ip:%s, close timer:%p", pContext, pContext->ipstr, pContext->timer);
    pContext->timer = NULL;
  }
}