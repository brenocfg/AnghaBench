#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ value; } ;
struct TYPE_9__ {TYPE_2__ def; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_3__ u; } ;
struct generic_link_hash_entry {TYPE_4__ root; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
struct TYPE_11__ {scalar_t__ value; TYPE_1__ udata; int /*<<< orphan*/ * section; } ;
typedef  TYPE_5__ asymbol ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 TYPE_5__** _bfd_generic_link_get_symbols (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_link_hash_defined ; 

__attribute__((used)) static void
perform_slip (bfd *abfd,
	      unsigned int slip,
	      asection *input_section,
	      bfd_vma value)
{
  asymbol **s;

  s = _bfd_generic_link_get_symbols (abfd);
  BFD_ASSERT (s != (asymbol **) NULL);

  /* Find all symbols past this point, and make them know
     what's happened.  */
  while (*s)
    {
      asymbol *p = *s;

      if (p->section == input_section)
	{
	  /* This was pointing into this section, so mangle it.  */
	  if (p->value > value)
	    {
	      p->value -=slip;

	      if (p->udata.p != NULL)
		{
		  struct generic_link_hash_entry *h;

		  h = (struct generic_link_hash_entry *) p->udata.p;
		  BFD_ASSERT (h->root.type == bfd_link_hash_defined);
		  h->root.u.def.value -= slip;
		  BFD_ASSERT (h->root.u.def.value == p->value);
		}
	    }
	}
      s++;
    }
}