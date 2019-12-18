#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* sy_previous; struct TYPE_7__* sy_next; } ;
typedef  TYPE_1__ symbolS ;

/* Variables and functions */
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_1__*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  debug_verify_symchain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  know (int) ; 
 int /*<<< orphan*/  symbol_lastP ; 
 int /*<<< orphan*/  symbol_rootP ; 

void
symbol_append (symbolS *addme, symbolS *target,
	       symbolS **rootPP, symbolS **lastPP)
{
  if (LOCAL_SYMBOL_CHECK (addme))
    abort ();
  if (target != NULL && LOCAL_SYMBOL_CHECK (target))
    abort ();

  if (target == NULL)
    {
      know (*rootPP == NULL);
      know (*lastPP == NULL);
      addme->sy_next = NULL;
      addme->sy_previous = NULL;
      *rootPP = addme;
      *lastPP = addme;
      return;
    }				/* if the list is empty  */

  if (target->sy_next != NULL)
    {
      target->sy_next->sy_previous = addme;
    }
  else
    {
      know (*lastPP == target);
      *lastPP = addme;
    }				/* if we have a next  */

  addme->sy_next = target->sy_next;
  target->sy_next = addme;
  addme->sy_previous = target;

  debug_verify_symchain (symbol_rootP, symbol_lastP);
}