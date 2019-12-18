#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  cond; } ;
struct TYPE_8__ {size_t numOfTagCond; TYPE_2__* cond; TYPE_1__ tbnameCond; } ;
struct TYPE_7__ {int /*<<< orphan*/  cond; } ;
typedef  TYPE_3__ STagCond ;

/* Variables and functions */
 int /*<<< orphan*/  SStringFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void tscTagCondRelease(STagCond* pCond) {
  SStringFree(&pCond->tbnameCond.cond);

  for (int32_t i = 0; i < pCond->numOfTagCond; ++i) {
    SStringFree(&pCond->cond[i].cond);
  }

  memset(pCond, 0, sizeof(STagCond));
}