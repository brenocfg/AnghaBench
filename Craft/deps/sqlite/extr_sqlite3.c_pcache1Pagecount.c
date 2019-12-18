#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_2__ {int nPage; int /*<<< orphan*/  pGroup; } ;
typedef  TYPE_1__ PCache1 ;

/* Variables and functions */
 int /*<<< orphan*/  pcache1EnterMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcache1LeaveMutex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcache1Pagecount(sqlite3_pcache *p){
  int n;
  PCache1 *pCache = (PCache1*)p;
  pcache1EnterMutex(pCache->pGroup);
  n = pCache->nPage;
  pcache1LeaveMutex(pCache->pGroup);
  return n;
}