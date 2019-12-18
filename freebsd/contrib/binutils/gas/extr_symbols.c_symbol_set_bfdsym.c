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
struct TYPE_7__ {TYPE_2__* bsym; } ;
typedef  TYPE_1__ symbolS ;
struct local_symbol {int dummy; } ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ asymbol ;

/* Variables and functions */
 int BSF_SECTION_SYM ; 
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_1__*) ; 
 TYPE_1__* local_symbol_convert (struct local_symbol*) ; 

void
symbol_set_bfdsym (symbolS *s, asymbol *bsym)
{
  if (LOCAL_SYMBOL_CHECK (s))
    s = local_symbol_convert ((struct local_symbol *) s);
  /* Usually, it is harmless to reset a symbol to a BFD section
     symbol. For example, obj_elf_change_section sets the BFD symbol
     of an old symbol with the newly created section symbol. But when
     we have multiple sections with the same name, the newly created
     section may have the same name as an old section. We check if the
     old symbol has been already marked as a section symbol before
     resetting it.  */
  if ((s->bsym->flags & BSF_SECTION_SYM) == 0)
    s->bsym = bsym;
  /* else XXX - What do we do now ?  */
}