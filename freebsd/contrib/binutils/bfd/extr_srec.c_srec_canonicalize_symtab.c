#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct srec_symbol {int /*<<< orphan*/  val; int /*<<< orphan*/  name; struct srec_symbol* next; } ;
typedef  int bfd_size_type ;
struct TYPE_12__ {TYPE_1__* srec_data; } ;
struct TYPE_14__ {TYPE_2__ tdata; } ;
typedef  TYPE_4__ bfd ;
struct TYPE_13__ {int /*<<< orphan*/ * p; } ;
struct TYPE_15__ {TYPE_3__ udata; int /*<<< orphan*/  section; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; int /*<<< orphan*/  name; TYPE_4__* the_bfd; } ;
typedef  TYPE_5__ asymbol ;
struct TYPE_11__ {struct srec_symbol* symbols; TYPE_5__* csymbols; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_GLOBAL ; 
 int /*<<< orphan*/  bfd_abs_section_ptr ; 
 TYPE_5__* bfd_alloc (TYPE_4__*,int) ; 
 int bfd_get_symcount (TYPE_4__*) ; 

__attribute__((used)) static long
srec_canonicalize_symtab (bfd *abfd, asymbol **alocation)
{
  bfd_size_type symcount = bfd_get_symcount (abfd);
  asymbol *csymbols;
  unsigned int i;

  csymbols = abfd->tdata.srec_data->csymbols;
  if (csymbols == NULL)
    {
      asymbol *c;
      struct srec_symbol *s;

      csymbols = bfd_alloc (abfd, symcount * sizeof (asymbol));
      if (csymbols == NULL && symcount != 0)
	return 0;
      abfd->tdata.srec_data->csymbols = csymbols;

      for (s = abfd->tdata.srec_data->symbols, c = csymbols;
	   s != NULL;
	   s = s->next, ++c)
	{
	  c->the_bfd = abfd;
	  c->name = s->name;
	  c->value = s->val;
	  c->flags = BSF_GLOBAL;
	  c->section = bfd_abs_section_ptr;
	  c->udata.p = NULL;
	}
    }

  for (i = 0; i < symcount; i++)
    *alocation++ = csymbols++;
  *alocation = NULL;

  return symcount;
}