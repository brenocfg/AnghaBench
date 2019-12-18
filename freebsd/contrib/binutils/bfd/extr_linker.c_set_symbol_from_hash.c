#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; int /*<<< orphan*/ * section; } ;
struct TYPE_8__ {TYPE_2__ c; TYPE_1__ def; } ;
struct bfd_link_hash_entry {int type; TYPE_3__ u; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/ * section; int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int BSF_CONSTRUCTOR ; 
 int BSF_WEAK ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * bfd_abs_section_ptr ; 
 void* bfd_com_section_ptr ; 
 int /*<<< orphan*/  bfd_is_com_section (int /*<<< orphan*/ *) ; 
 int bfd_is_und_section (int /*<<< orphan*/ *) ; 
#define  bfd_link_hash_common 135 
#define  bfd_link_hash_defined 134 
#define  bfd_link_hash_defweak 133 
#define  bfd_link_hash_indirect 132 
#define  bfd_link_hash_new 131 
#define  bfd_link_hash_undefined 130 
#define  bfd_link_hash_undefweak 129 
#define  bfd_link_hash_warning 128 
 void* bfd_und_section_ptr ; 

__attribute__((used)) static void
set_symbol_from_hash (asymbol *sym, struct bfd_link_hash_entry *h)
{
  switch (h->type)
    {
    default:
      abort ();
      break;
    case bfd_link_hash_new:
      /* This can happen when a constructor symbol is seen but we are
         not building constructors.  */
      if (sym->section != NULL)
	{
	  BFD_ASSERT ((sym->flags & BSF_CONSTRUCTOR) != 0);
	}
      else
	{
	  sym->flags |= BSF_CONSTRUCTOR;
	  sym->section = bfd_abs_section_ptr;
	  sym->value = 0;
	}
      break;
    case bfd_link_hash_undefined:
      sym->section = bfd_und_section_ptr;
      sym->value = 0;
      break;
    case bfd_link_hash_undefweak:
      sym->section = bfd_und_section_ptr;
      sym->value = 0;
      sym->flags |= BSF_WEAK;
      break;
    case bfd_link_hash_defined:
      sym->section = h->u.def.section;
      sym->value = h->u.def.value;
      break;
    case bfd_link_hash_defweak:
      sym->flags |= BSF_WEAK;
      sym->section = h->u.def.section;
      sym->value = h->u.def.value;
      break;
    case bfd_link_hash_common:
      sym->value = h->u.c.size;
      if (sym->section == NULL)
	sym->section = bfd_com_section_ptr;
      else if (! bfd_is_com_section (sym->section))
	{
	  BFD_ASSERT (bfd_is_und_section (sym->section));
	  sym->section = bfd_com_section_ptr;
	}
      /* Do not set the section; see _bfd_generic_link_output_symbols.  */
      break;
    case bfd_link_hash_indirect:
    case bfd_link_hash_warning:
      /* FIXME: What should we do here?  */
      break;
    }
}