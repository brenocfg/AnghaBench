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
typedef  int /*<<< orphan*/  ILookInStream ;
typedef  int /*<<< orphan*/  CSzData ;
typedef  int /*<<< orphan*/  CSzAr ;
typedef  int /*<<< orphan*/  CBuf ;

/* Variables and functions */
 int /*<<< orphan*/  IAlloc_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SzAr_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SzAr_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SzReadAndDecodePackedStreams2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SRes SzReadAndDecodePackedStreams(
      ILookInStream *inStream,
      CSzData *sd,
      CBuf *outBuffer,
      uint64_t baseOffset,
      ISzAlloc *allocTemp)
{
   CSzAr p;
   uint64_t *unpackSizes = 0;
   uint8_t *digestsDefined = 0;
   uint32_t *digests = 0;
   SRes res;
   SzAr_Init(&p);
   res = SzReadAndDecodePackedStreams2(inStream, sd, outBuffer, baseOffset,
         &p, &unpackSizes, &digestsDefined, &digests,
         allocTemp);
   SzAr_Free(&p, allocTemp);
   IAlloc_Free(allocTemp, unpackSizes);
   IAlloc_Free(allocTemp, digestsDefined);
   IAlloc_Free(allocTemp, digests);
   return res;
}