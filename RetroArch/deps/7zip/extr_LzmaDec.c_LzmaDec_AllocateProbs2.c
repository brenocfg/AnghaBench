#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int numProbs; int /*<<< orphan*/ * probs; } ;
struct TYPE_8__ {scalar_t__ (* Alloc ) (TYPE_1__*,int) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ISzAlloc ;
typedef  int /*<<< orphan*/  CLzmaProps ;
typedef  TYPE_2__ CLzmaDec ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaDec_FreeProbs (TYPE_2__*,TYPE_1__*) ; 
 int LzmaProps_GetNumProbs (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 scalar_t__ stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static SRes LzmaDec_AllocateProbs2(CLzmaDec *p, const CLzmaProps *propNew, ISzAlloc *alloc)
{
   uint32_t numProbs = LzmaProps_GetNumProbs(propNew);
   if (p->probs == 0 || numProbs != p->numProbs)
   {
      LzmaDec_FreeProbs(p, alloc);
      p->probs = (uint16_t *)alloc->Alloc(alloc, numProbs * sizeof(uint16_t));
      p->numProbs = numProbs;
      if (p->probs == 0)
         return SZ_ERROR_MEM;
   }
   return SZ_OK;
}