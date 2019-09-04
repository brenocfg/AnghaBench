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
struct TYPE_6__ {TYPE_3__* pNC; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_8__ {scalar_t__ nDepth; } ;
typedef  int /*<<< orphan*/  Select ;
typedef  TYPE_3__ NameContext ;

/* Variables and functions */
 int WRC_Continue ; 
 int WRC_Prune ; 
 int /*<<< orphan*/  sqlite3WalkSelect (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int analyzeAggregatesInSelect(Walker *pWalker, Select *pSelect){
  NameContext *pNC = pWalker->u.pNC;
  if( pNC->nDepth==0 ){
    pNC->nDepth++;
    sqlite3WalkSelect(pWalker, pSelect);
    pNC->nDepth--;
    return WRC_Prune;
  }else{
    return WRC_Continue;
  }
}