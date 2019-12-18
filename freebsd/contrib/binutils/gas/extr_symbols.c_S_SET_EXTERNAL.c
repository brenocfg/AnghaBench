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
struct TYPE_8__ {TYPE_1__* bsym; } ;
typedef  TYPE_2__ symbolS ;
struct local_symbol {int dummy; } ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 int BSF_SECTION_SYM ; 
 int BSF_WEAK ; 
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_2__*) ; 
 char* S_GET_NAME (TYPE_2__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* an_external_name ; 
 int /*<<< orphan*/  as_warn_where (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_where (char**,unsigned int*) ; 
 TYPE_2__* local_symbol_convert (struct local_symbol*) ; 

void
S_SET_EXTERNAL (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    s = local_symbol_convert ((struct local_symbol *) s);
  if ((s->bsym->flags & BSF_WEAK) != 0)
    {
      /* Let .weak override .global.  */
      return;
    }
  if (s->bsym->flags & BSF_SECTION_SYM)
    {
      char * file;
      unsigned int line;

      /* Do not reassign section symbols.  */
      as_where (& file, & line);
      as_warn_where (file, line,
		     _("section symbols are already global"));
      return;
    }
  s->bsym->flags |= BSF_GLOBAL;
  s->bsym->flags &= ~(BSF_LOCAL | BSF_WEAK);

#ifdef USE_UNIQUE
  if (! an_external_name && S_GET_NAME(s)[0] != '.')
    an_external_name = S_GET_NAME (s);
#endif
}