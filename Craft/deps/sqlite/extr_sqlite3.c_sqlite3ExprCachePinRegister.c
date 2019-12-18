#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct yColCache {int iReg; scalar_t__ tempReg; } ;
struct TYPE_3__ {struct yColCache* aColCache; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int SQLITE_N_COLCACHE ; 

__attribute__((used)) static void sqlite3ExprCachePinRegister(Parse *pParse, int iReg){
  int i;
  struct yColCache *p;
  for(i=0, p=pParse->aColCache; i<SQLITE_N_COLCACHE; i++, p++){
    if( p->iReg==iReg ){
      p->tempReg = 0;
    }
  }
}