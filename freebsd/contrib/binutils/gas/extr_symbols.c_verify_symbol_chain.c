#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* sy_next; int /*<<< orphan*/ * bsym; } ;
typedef  TYPE_2__ symbolS ;
struct TYPE_7__ {TYPE_2__* sy_previous; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* symbol_next (TYPE_2__*) ; 

void
verify_symbol_chain (symbolS *rootP, symbolS *lastP)
{
  symbolS *symbolP = rootP;

  if (symbolP == NULL)
    return;

  for (; symbol_next (symbolP) != NULL; symbolP = symbol_next (symbolP))
    {
      assert (symbolP->bsym != NULL);
      assert (symbolP->sy_next->sy_previous == symbolP);
    }

  assert (lastP == symbolP);
}