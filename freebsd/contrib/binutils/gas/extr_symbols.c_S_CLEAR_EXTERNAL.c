#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* bsym; } ;
typedef  TYPE_2__ symbolS ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 int BSF_WEAK ; 
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_2__*) ; 

void
S_CLEAR_EXTERNAL (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    return;
  if ((s->bsym->flags & BSF_WEAK) != 0)
    {
      /* Let .weak override.  */
      return;
    }
  s->bsym->flags |= BSF_LOCAL;
  s->bsym->flags &= ~(BSF_GLOBAL | BSF_WEAK);
}