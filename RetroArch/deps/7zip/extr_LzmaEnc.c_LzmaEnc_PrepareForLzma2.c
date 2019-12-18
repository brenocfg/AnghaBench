#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * stream; } ;
struct TYPE_5__ {int needInit; TYPE_1__ matchFinderBase; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  TYPE_2__ CLzmaEnc ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaEnc_AllocAndInit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

SRes LzmaEnc_PrepareForLzma2(CLzmaEncHandle pp,
    ISeqInStream *inStream, uint32_t keepWindowSize,
    ISzAlloc *alloc, ISzAlloc *allocBig)
{
  CLzmaEnc *p = (CLzmaEnc *)pp;
  p->matchFinderBase.stream = inStream;
  p->needInit = 1;
  return LzmaEnc_AllocAndInit(p, keepWindowSize, alloc, allocBig);
}