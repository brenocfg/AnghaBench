#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* bsym; scalar_t__ sy_weakrefd; } ;
typedef  TYPE_2__ symbolS ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int BSF_LOCAL ; 
 int BSF_WEAK ; 
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_2__*) ; 
 int /*<<< orphan*/  obj_clear_weak_hook (TYPE_2__*) ; 

void
S_CLEAR_WEAKREFD (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    return;
  if (s->sy_weakrefd)
    {
      s->sy_weakrefd = 0;
      /* If a weakref target symbol is weak, then it was never
	 referenced directly before, not even in a .global directive,
	 so decay it to local.  If it remains undefined, it will be
	 later turned into a global, like any other undefined
	 symbol.  */
      if (s->bsym->flags & BSF_WEAK)
	{
#ifdef obj_clear_weak_hook
	  obj_clear_weak_hook (s);
#endif
	  s->bsym->flags &= ~BSF_WEAK;
	  s->bsym->flags |= BSF_LOCAL;
	}
    }
}