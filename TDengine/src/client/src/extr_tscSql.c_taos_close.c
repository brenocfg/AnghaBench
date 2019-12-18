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
struct TYPE_4__ {int /*<<< orphan*/ * pHb; struct TYPE_4__* signature; } ;
typedef  int /*<<< orphan*/  TAOS ;
typedef  TYPE_1__ STscObj ;

/* Variables and functions */
 int /*<<< orphan*/  tscCloseTscObj (TYPE_1__*) ; 
 int /*<<< orphan*/  tscSetFreeHeatBeat (TYPE_1__*) ; 

void taos_close(TAOS *taos) {
  STscObj *pObj = (STscObj *)taos;

  if (pObj == NULL) return;
  if (pObj->signature != pObj) return;

  if (pObj->pHb != NULL) {
    tscSetFreeHeatBeat(pObj);
  } else {
    tscCloseTscObj(pObj);
  }
}