#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ X_op; int /*<<< orphan*/ * X_op_symbol; } ;
struct TYPE_9__ {TYPE_1__ sy_value; scalar_t__ sy_resolved; } ;
typedef  TYPE_2__ symbolS ;

/* Variables and functions */
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_2__*) ; 
 scalar_t__ O_symbol ; 
 scalar_t__ S_IS_COMMON (TYPE_2__*) ; 
 int /*<<< orphan*/  S_IS_DEFINED (TYPE_2__*) ; 
 int /*<<< orphan*/  S_IS_WEAK (TYPE_2__*) ; 

int
symbol_equated_reloc_p (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    return 0;
  /* X_op_symbol, normally not used for O_symbol, is set by
     resolve_symbol_value to flag expression syms that have been
     equated.  */
  return (s->sy_value.X_op == O_symbol
#if defined (OBJ_COFF) && defined (TE_PE)
	  && ! S_IS_WEAK (s)
#endif
	  && ((s->sy_resolved && s->sy_value.X_op_symbol != NULL)
	      || ! S_IS_DEFINED (s)
	      || S_IS_COMMON (s)));
}