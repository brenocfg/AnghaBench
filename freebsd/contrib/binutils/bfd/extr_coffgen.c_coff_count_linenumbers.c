#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* section; } ;
struct TYPE_13__ {TYPE_2__ symbol; TYPE_6__* lineno; } ;
typedef  TYPE_3__ coff_symbol_type ;
struct TYPE_14__ {int /*<<< orphan*/ ** outsymbols; TYPE_5__* sections; } ;
typedef  TYPE_4__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_15__ {scalar_t__ lineno_count; struct TYPE_15__* next; } ;
typedef  TYPE_5__ asection ;
struct TYPE_16__ {scalar_t__ line_number; } ;
typedef  TYPE_6__ alent ;
struct TYPE_11__ {TYPE_5__* output_section; int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  bfd_asymbol_bfd (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_family_coff (int /*<<< orphan*/ ) ; 
 unsigned int bfd_get_symcount (TYPE_4__*) ; 
 int /*<<< orphan*/  bfd_is_const_section (TYPE_5__*) ; 
 TYPE_3__* coffsymbol (int /*<<< orphan*/ *) ; 

int
coff_count_linenumbers (bfd *abfd)
{
  unsigned int limit = bfd_get_symcount (abfd);
  unsigned int i;
  int total = 0;
  asymbol **p;
  asection *s;

  if (limit == 0)
    {
      /* This may be from the backend linker, in which case the
         lineno_count in the sections is correct.  */
      for (s = abfd->sections; s != NULL; s = s->next)
	total += s->lineno_count;
      return total;
    }

  for (s = abfd->sections; s != NULL; s = s->next)
    BFD_ASSERT (s->lineno_count == 0);

  for (p = abfd->outsymbols, i = 0; i < limit; i++, p++)
    {
      asymbol *q_maybe = *p;

      if (bfd_family_coff (bfd_asymbol_bfd (q_maybe)))
	{
	  coff_symbol_type *q = coffsymbol (q_maybe);

	  /* The AIX 4.1 compiler can sometimes generate line numbers
             attached to debugging symbols.  We try to simply ignore
             those here.  */
	  if (q->lineno != NULL
	      && q->symbol.section->owner != NULL)
	    {
	      /* This symbol has line numbers.  Increment the owning
	         section's linenumber count.  */
	      alent *l = q->lineno;

	      do
		{
		  asection * sec = q->symbol.section->output_section;

		  /* Do not try to update fields in read-only sections.  */
		  if (! bfd_is_const_section (sec))
		    sec->lineno_count ++;

		  ++total;
		  ++l;
		}
	      while (l->line_number != 0);
	    }
	}
    }

  return total;
}