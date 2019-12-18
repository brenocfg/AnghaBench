#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {TYPE_4__* callbacks; } ;
struct TYPE_13__ {scalar_t__ size; } ;
struct TYPE_12__ {int /*<<< orphan*/  section; scalar_t__ value; } ;
struct TYPE_14__ {TYPE_2__ c; TYPE_1__ def; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_3__ u; } ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_16__ {int /*<<< orphan*/  section; scalar_t__ value; } ;
typedef  TYPE_5__ asymbol ;
struct TYPE_17__ {int /*<<< orphan*/  owner; } ;
typedef  TYPE_6__ asection ;
struct TYPE_18__ {scalar_t__ addend; int /*<<< orphan*/  address; TYPE_5__** sym_ptr_ptr; } ;
typedef  TYPE_7__ arelent ;
struct TYPE_15__ {int /*<<< orphan*/  (* undefined_symbol ) (struct bfd_link_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_asymbol_name (TYPE_5__*) ; 
 scalar_t__ bfd_is_und_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_common ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 struct bfd_link_hash_entry* bfd_wrapped_link_hash_lookup (int /*<<< orphan*/ ,struct bfd_link_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ output_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct bfd_link_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_vma
get_value (arelent *reloc,
	   struct bfd_link_info *link_info,
	   asection *input_section)
{
  bfd_vma value;
  asymbol *symbol = *(reloc->sym_ptr_ptr);

  /* A symbol holds a pointer to a section, and an offset from the
     base of the section.  To relocate, we find where the section will
     live in the output and add that in.  */
  if (bfd_is_und_section (symbol->section))
    {
      struct bfd_link_hash_entry *h;

      /* The symbol is undefined in this BFD.  Look it up in the
	 global linker hash table.  FIXME: This should be changed when
	 we convert b.out to use a specific final_link function and
	 change the interface to bfd_relax_section to not require the
	 generic symbols.  */
      h = bfd_wrapped_link_hash_lookup (input_section->owner, link_info,
					bfd_asymbol_name (symbol),
					FALSE, FALSE, TRUE);
      if (h != (struct bfd_link_hash_entry *) NULL
	  && (h->type == bfd_link_hash_defined
	      || h->type == bfd_link_hash_defweak))
	value = h->u.def.value + output_addr (h->u.def.section);
      else if (h != (struct bfd_link_hash_entry *) NULL
	       && h->type == bfd_link_hash_common)
	value = h->u.c.size;
      else
	{
	  if (! ((*link_info->callbacks->undefined_symbol)
		 (link_info, bfd_asymbol_name (symbol),
		  input_section->owner, input_section, reloc->address,
		  TRUE)))
	    abort ();
	  value = 0;
	}
    }
  else
    value = symbol->value + output_addr (symbol->section);

  /* Add the value contained in the relocation.  */
  value += reloc->addend;

  return value;
}