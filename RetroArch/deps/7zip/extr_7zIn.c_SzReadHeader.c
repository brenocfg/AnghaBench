#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  int /*<<< orphan*/  CSzData ;
typedef  int /*<<< orphan*/  CSzArEx ;

/* Variables and functions */
 int /*<<< orphan*/  IAlloc_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SzReadHeader2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SRes SzReadHeader(
      CSzArEx *p,
      CSzData *sd,
      ISzAlloc *allocMain,
      ISzAlloc *allocTemp)
{
   uint64_t *unpackSizes = 0;
   uint8_t *digestsDefined = 0;
   uint32_t *digests = 0;
   uint8_t *emptyStreamVector = 0;
   uint8_t *emptyFileVector = 0;
   uint8_t *lwtVector = 0;
   SRes res = SzReadHeader2(p, sd,
         &unpackSizes, &digestsDefined, &digests,
         &emptyStreamVector, &emptyFileVector, &lwtVector,
         allocMain, allocTemp);
   IAlloc_Free(allocTemp, unpackSizes);
   IAlloc_Free(allocTemp, digestsDefined);
   IAlloc_Free(allocTemp, digests);
   IAlloc_Free(allocTemp, emptyStreamVector);
   IAlloc_Free(allocTemp, emptyFileVector);
   IAlloc_Free(allocTemp, lwtVector);
   return res;
}