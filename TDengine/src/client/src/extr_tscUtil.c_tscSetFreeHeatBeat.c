#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_1__ cmd; struct TYPE_7__* signature; } ;
struct TYPE_6__ {TYPE_3__* pHb; struct TYPE_6__* signature; } ;
typedef  TYPE_2__ STscObj ;
typedef  TYPE_3__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_QUERY_TYPE_FREE_RESOURCE ; 
 int /*<<< orphan*/  assert (int) ; 

void tscSetFreeHeatBeat(STscObj* pObj) {
  if (pObj == NULL || pObj->signature != pObj || pObj->pHb == NULL) {
    return;
  }

  SSqlObj* pHeatBeat = pObj->pHb;
  assert(pHeatBeat == pHeatBeat->signature);

  // to denote the heart-beat timer close connection and free all allocated resources
  pHeatBeat->cmd.type = TSDB_QUERY_TYPE_FREE_RESOURCE;
}