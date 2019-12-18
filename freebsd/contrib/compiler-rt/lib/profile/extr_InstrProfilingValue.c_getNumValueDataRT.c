#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {scalar_t__** SiteCountArray; TYPE_1__* Data; } ;
typedef  TYPE_2__ ValueProfRuntimeRecord ;
struct TYPE_3__ {size_t* NumValueSites; } ;

/* Variables and functions */
 scalar_t__* INSTR_PROF_NULLPTR ; 

__attribute__((used)) static uint32_t getNumValueDataRT(const void *R, uint32_t VK) {
  uint32_t S = 0, I;
  const ValueProfRuntimeRecord *Record = (const ValueProfRuntimeRecord *)R;
  if (Record->SiteCountArray[VK] == INSTR_PROF_NULLPTR)
    return 0;
  for (I = 0; I < Record->Data->NumValueSites[VK]; I++)
    S += Record->SiteCountArray[VK][I];
  return S;
}