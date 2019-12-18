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
struct local_symbol {scalar_t__ lsy_section; } ;
struct TYPE_5__ {int flags; scalar_t__ section; } ;

/* Variables and functions */
 int BSF_GLOBAL ; 
 int BSF_WEAK ; 
 scalar_t__ EXTERN_FORCE_RELOC ; 
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_2__*) ; 
 scalar_t__ bfd_is_com_section (scalar_t__) ; 
 scalar_t__ undefined_section ; 

int
S_FORCE_RELOC (symbolS *s, int strict)
{
  if (LOCAL_SYMBOL_CHECK (s))
    return ((struct local_symbol *) s)->lsy_section == undefined_section;

  return ((strict
	   && ((s->bsym->flags & BSF_WEAK) != 0
	       || (EXTERN_FORCE_RELOC
		   && (s->bsym->flags & BSF_GLOBAL) != 0)))
	  || s->bsym->section == undefined_section
	  || bfd_is_com_section (s->bsym->section));
}