#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* sy_next; struct TYPE_8__* sy_previous; } ;
typedef  TYPE_1__ symbolS ;

/* Variables and functions */
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_1__*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  debug_verify_symchain (TYPE_1__*,TYPE_1__*) ; 

void
symbol_remove (symbolS *symbolP, symbolS **rootPP, symbolS **lastPP)
{
  if (LOCAL_SYMBOL_CHECK (symbolP))
    abort ();

  if (symbolP == *rootPP)
    {
      *rootPP = symbolP->sy_next;
    }				/* if it was the root  */

  if (symbolP == *lastPP)
    {
      *lastPP = symbolP->sy_previous;
    }				/* if it was the tail  */

  if (symbolP->sy_next != NULL)
    {
      symbolP->sy_next->sy_previous = symbolP->sy_previous;
    }				/* if not last  */

  if (symbolP->sy_previous != NULL)
    {
      symbolP->sy_previous->sy_next = symbolP->sy_next;
    }				/* if not first  */

  debug_verify_symchain (*rootPP, *lastPP);
}