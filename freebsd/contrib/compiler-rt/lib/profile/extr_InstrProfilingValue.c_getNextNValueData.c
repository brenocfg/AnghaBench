#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_7__ {struct TYPE_7__* Next; int /*<<< orphan*/  Count; int /*<<< orphan*/  Value; } ;
typedef  TYPE_1__ ValueProfNode ;
struct TYPE_9__ {TYPE_1__*** NodesKind; } ;
struct TYPE_8__ {int /*<<< orphan*/  Count; int /*<<< orphan*/  Value; } ;
typedef  TYPE_2__ InstrProfValueData ;

/* Variables and functions */
 TYPE_6__ RTRecord ; 

__attribute__((used)) static ValueProfNode *getNextNValueData(uint32_t VK, uint32_t Site,
                                        InstrProfValueData *Dst,
                                        ValueProfNode *StartNode, uint32_t N) {
  unsigned I;
  ValueProfNode *VNode = StartNode ? StartNode : RTRecord.NodesKind[VK][Site];
  for (I = 0; I < N; I++) {
    Dst[I].Value = VNode->Value;
    Dst[I].Count = VNode->Count;
    VNode = VNode->Next;
  }
  return VNode;
}