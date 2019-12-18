#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptw32_srwl_rwlock_t ;
struct TYPE_6__ {TYPE_4__* departFromPtr; int /*<<< orphan*/  ticket; } ;
typedef  TYPE_2__ ptw32_srwl_local_t ;
struct TYPE_7__ {TYPE_1__* qNextPtr; int /*<<< orphan*/  csnzi; } ;
struct TYPE_5__ {int /*<<< orphan*/  spin; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTW32_FALSE ; 
 scalar_t__ ptw32_oll_Depart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptw32_srwl_FreeReaderNode (TYPE_4__*) ; 

void
ptw32_srwl_ReaderUnlock(ptw32_srwl_rwlock_t* lockPtr, ptw32_srwl_local_t* localPtr)
{
  if (ptw32_oll_Depart(localPtr->departFromPtr->csnzi, localPtr->ticket))
  {
    return;
  }
  /* Clean up */
  localPtr->departFromPtr->qNextPtr->spin = PTW32_FALSE;
  localPtr->departFromPtr->qNextPtr = NULL;
  ptw32_srwl_FreeReaderNode(localPtr->departFromPtr);
}