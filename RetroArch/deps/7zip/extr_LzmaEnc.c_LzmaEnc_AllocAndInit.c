#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int dictSize; int distTableSize; int finished; scalar_t__ nowPos64; int /*<<< orphan*/  result; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaEnc_Alloc (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaEnc_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  LzmaEnc_InitPrices (TYPE_1__*) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 
 scalar_t__ kDicLogSizeMaxCompress ; 

__attribute__((used)) static SRes LzmaEnc_AllocAndInit(CLzmaEnc *p, uint32_t keepWindowSize, ISzAlloc *alloc, ISzAlloc *allocBig)
{
  uint32_t i;
  for (i = 0; i < (uint32_t)kDicLogSizeMaxCompress; i++)
    if (p->dictSize <= ((uint32_t)1 << i))
      break;
  p->distTableSize = i * 2;

  p->finished = false;
  p->result = SZ_OK;
  RINOK(LzmaEnc_Alloc(p, keepWindowSize, alloc, allocBig));
  LzmaEnc_Init(p);
  LzmaEnc_InitPrices(p);
  p->nowPos64 = 0;
  return SZ_OK;
}