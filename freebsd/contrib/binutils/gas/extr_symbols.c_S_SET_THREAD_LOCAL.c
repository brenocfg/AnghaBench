#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* bsym; } ;
typedef  TYPE_2__ symbolS ;
struct local_symbol {int dummy; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_9__ {int flags; TYPE_4__* section; } ;

/* Variables and functions */
 int BSF_FUNCTION ; 
 int BSF_THREAD_LOCAL ; 
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_2__*) ; 
 int SEC_THREAD_LOCAL ; 
 int /*<<< orphan*/  S_GET_NAME (TYPE_2__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_is_com_section (TYPE_4__*) ; 
 int /*<<< orphan*/  bfd_is_und_section (TYPE_4__*) ; 
 TYPE_2__* local_symbol_convert (struct local_symbol*) ; 

void
S_SET_THREAD_LOCAL (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    s = local_symbol_convert ((struct local_symbol *) s);
  if (bfd_is_com_section (s->bsym->section)
      && (s->bsym->flags & BSF_THREAD_LOCAL) != 0)
    return;
  s->bsym->flags |= BSF_THREAD_LOCAL;
  if ((s->bsym->flags & BSF_FUNCTION) != 0)
    as_bad (_("Accessing function `%s' as thread-local object"),
	    S_GET_NAME (s));
  else if (! bfd_is_und_section (s->bsym->section)
	   && (s->bsym->section->flags & SEC_THREAD_LOCAL) == 0)
    as_bad (_("Accessing `%s' as thread-local object"),
	    S_GET_NAME (s));
}