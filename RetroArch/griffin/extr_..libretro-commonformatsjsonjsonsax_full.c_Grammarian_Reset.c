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
struct TYPE_3__ {int stackSize; int stackUsed; int /*<<< orphan*/ * pStack; int /*<<< orphan*/ * defaultStack; } ;
typedef  TYPE_1__* Grammarian ;

/* Variables and functions */
 int /*<<< orphan*/  NT_VALUE ; 

__attribute__((used)) static void Grammarian_Reset(Grammarian grammarian, int isInitialized)
{
   /* When we reset the grammarian, we keep the symbol stack that has
      already been allocated, if any. If the client wants to reclaim the
      memory used by the that buffer, he needs to free the grammarian
      and create a new one. */
   if (!isInitialized)
   {
      grammarian->pStack = grammarian->defaultStack;
      grammarian->stackSize = sizeof(grammarian->defaultStack);
   }

   /* The grammarian always starts with NT_VALUE on the symbol stack. */
   grammarian->pStack[0] = NT_VALUE;
   grammarian->stackUsed = 1;
}