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
typedef  scalar_t__ yyyRCT ;
struct TYPE_3__ {int refCountListLen; int cLlen; struct TYPE_3__** cL; scalar_t__* refCountList; } ;
typedef  TYPE_1__ yyyGNT ;

/* Variables and functions */

void yyyCheckUnsolvedInstTrav(yyyGNT *pNode,long *nNZrc,long *cycleSum)
  {yyyGNT **yyyCLpdum;
   yyyRCT *rcp;
   int i;
  
   /* visit the refCountList of each node in the tree, and sum the non-zero refCounts */ 
   rcp = pNode->refCountList; 
   i = pNode->refCountListLen; 
   while (i--) 
      if (*rcp++) {*cycleSum += *(rcp - 1); (*nNZrc)++;} 
   yyyCLpdum = pNode->cL;
   i = pNode->cLlen;
   while (i--)
     {
      yyyCheckUnsolvedInstTrav(*yyyCLpdum,nNZrc,cycleSum);
      yyyCLpdum++;
     }
  }