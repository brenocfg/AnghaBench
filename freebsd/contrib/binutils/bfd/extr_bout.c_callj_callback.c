#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int dummy; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_8__ {int addend; int /*<<< orphan*/ ** sym_ptr_ptr; } ;
typedef  TYPE_2__ arelent ;
struct TYPE_7__ {int value; int flags; int /*<<< orphan*/ * section; } ;
struct TYPE_9__ {int other; TYPE_1__ symbol; } ;
typedef  TYPE_3__ aout_symbol_type ;

/* Variables and functions */
 int BAL ; 
 int BAL_MASK ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int BSF_SECTION_SYM ; 
 int CALL ; 
 int CALLS ; 
 int IS_BALNAME (int) ; 
 scalar_t__ IS_CALLNAME (int) ; 
 scalar_t__ IS_OTHER (int) ; 
 TYPE_3__* aout_symbol (int /*<<< orphan*/ *) ; 
 int bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_reloc_ok ; 
 int get_value (TYPE_2__*,struct bfd_link_info*,int /*<<< orphan*/ *) ; 
 int output_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_reloc_status_type
callj_callback (bfd *abfd,
		struct bfd_link_info *link_info,
		arelent *reloc_entry,
		void * data,
		unsigned int srcidx,
		unsigned int dstidx,
		asection *input_section,
		bfd_boolean shrinking)
{
  int word = bfd_get_32 (abfd, (bfd_byte *) data + srcidx);
  asymbol *symbol_in = *(reloc_entry->sym_ptr_ptr);
  aout_symbol_type *symbol = aout_symbol (symbol_in);
  bfd_vma value;

  value = get_value (reloc_entry, link_info, input_section);

  if (IS_OTHER (symbol->other))
    /* Call to a system procedure - replace code with system
       procedure number.  */
    word = CALLS | (symbol->other - 1);

  else if (IS_CALLNAME (symbol->other))
    {
      aout_symbol_type *balsym = symbol+1;

      /* The next symbol should be an N_BALNAME.  */
      BFD_ASSERT (IS_BALNAME (balsym->other));

      /* We are calling a leaf, so replace the call instruction with a
	 bal.  */
      word = BAL | ((word
		     + output_addr (balsym->symbol.section)
		     + balsym->symbol.value + reloc_entry->addend
		     - dstidx
		     - output_addr (input_section))
		    & BAL_MASK);
    }
  else if ((symbol->symbol.flags & BSF_SECTION_SYM) != 0)
    {
      /* A callj against a symbol in the same section is a fully
         resolved relative call.  We don't need to do anything here.
         If the symbol is not in the same section, I'm not sure what
         to do; fortunately, this case will probably never arise.  */
      BFD_ASSERT (! shrinking);
      BFD_ASSERT (symbol->symbol.section == input_section);
    }
  else
    word = CALL | (((word & BAL_MASK)
		    + value
		    + reloc_entry->addend
		    - (shrinking ? dstidx : 0)
		    - output_addr (input_section))
		   & BAL_MASK);

  bfd_put_32 (abfd, (bfd_vma) word, (bfd_byte *) data + dstidx);
  return bfd_reloc_ok;
}