#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * nodePtr; TYPE_5__* rootPtr; } ;
struct TYPE_12__ {TYPE_3__ snziNodeOrRoot; } ;
typedef  TYPE_4__ ptw32_oll_ticket_t ;
struct TYPE_9__ {scalar_t__ state; int /*<<< orphan*/  count; } ;
struct TYPE_10__ {scalar_t__ word; TYPE_1__ internal; } ;
struct TYPE_13__ {TYPE_2__ counter; } ;
typedef  TYPE_5__ ptw32_oll_snziRoot_t ;
typedef  int /*<<< orphan*/  ptw32_oll_snziNode_t ;
struct TYPE_14__ {int /*<<< orphan*/ * leafs; TYPE_5__ proxyRoot; } ;
typedef  TYPE_6__ ptw32_oll_csnzi_t ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_SIZEPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_SIZE ;

/* Variables and functions */
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_SIZE (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 size_t ptw32_oll_GetLeafForThread () ; 
 int /*<<< orphan*/  ptw32_oll_ShouldArriveAtTree () ; 
 scalar_t__ ptw32_oll_TreeArrive (int /*<<< orphan*/ *) ; 
 scalar_t__ ptw32_oll_snziRoot_open ; 

ptw32_oll_ticket_t
ptw32_oll_Arrive(ptw32_oll_csnzi_t* csnzi)
{
  for (;;)
  {
    ptw32_oll_ticket_t ticket;
    ptw32_oll_snziRoot_t oldProxy = csnzi->proxyRoot;
    if (oldProxy.counter.internal.state != ptw32_oll_snziRoot_open)
    {
      ticket.snziNodeOrRoot.rootPtr = (ptw32_oll_snziRoot_t*)NULL;
      return ticket;
    }
    if (!ptw32_oll_ShouldArriveAtTree())
    {
      ptw32_oll_snziRoot_t newProxy = oldProxy;
      newProxy.counter.internal.count++;
      if (PTW32_INTERLOCKED_COMPARE_EXCHANGE_SIZE(
                (PTW32_INTERLOCKED_SIZEPTR)&csnzi->proxyRoot.counter,
                (PTW32_INTERLOCKED_SIZE)newProxy.counter.word,
                (PTW32_INTERLOCKED_SIZE)oldProxy.counter.word)
          == (PTW32_INTERLOCKED_SIZE)oldProxy.counter.word)
      {
        /* Exchange successful */
        ticket.snziNodeOrRoot.rootPtr = &csnzi->proxyRoot;
        return ticket;
      }
    }
    else
    {
      ptw32_oll_snziNode_t* leafPtr = &csnzi->leafs[ptw32_oll_GetLeafForThread()];
      ticket.snziNodeOrRoot.nodePtr = (ptw32_oll_TreeArrive(leafPtr) ? leafPtr : (ptw32_oll_snziNode_t*)NULL);
      return ticket;
    }
  }
}