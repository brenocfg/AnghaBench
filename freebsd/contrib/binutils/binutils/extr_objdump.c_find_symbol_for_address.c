#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct objdump_disasm_info {scalar_t__ require_sec; int /*<<< orphan*/ * sec; TYPE_1__* abfd; } ;
struct disassemble_info {scalar_t__ (* symbol_is_valid ) (TYPE_2__*,struct disassemble_info*) ;scalar_t__ application_data; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_boolean ;
struct TYPE_13__ {int flags; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_14__ {int /*<<< orphan*/ * section; } ;
typedef  TYPE_2__ asymbol ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int HAS_RELOC ; 
 scalar_t__ bfd_asymbol_value (TYPE_2__*) ; 
 scalar_t__ bfd_get_section_vma (TYPE_1__*,int /*<<< orphan*/ *) ; 
 unsigned int bfd_octets_per_byte (TYPE_1__*) ; 
 unsigned int bfd_section_size (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int sorted_symcount ; 
 TYPE_2__** sorted_syms ; 
 scalar_t__ stub1 (TYPE_2__*,struct disassemble_info*) ; 
 scalar_t__ stub2 (TYPE_2__*,struct disassemble_info*) ; 
 scalar_t__ stub3 (TYPE_2__*,struct disassemble_info*) ; 
 scalar_t__ stub4 (TYPE_2__*,struct disassemble_info*) ; 

__attribute__((used)) static asymbol *
find_symbol_for_address (bfd_vma vma,
			 struct disassemble_info *info,
			 long *place)
{
  /* @@ Would it speed things up to cache the last two symbols returned,
     and maybe their address ranges?  For many processors, only one memory
     operand can be present at a time, so the 2-entry cache wouldn't be
     constantly churned by code doing heavy memory accesses.  */

  /* Indices in `sorted_syms'.  */
  long min = 0;
  long max = sorted_symcount;
  long thisplace;
  struct objdump_disasm_info *aux;
  bfd *abfd;
  asection *sec;
  unsigned int opb;
  bfd_boolean want_section;

  if (sorted_symcount < 1)
    return NULL;

  aux = (struct objdump_disasm_info *) info->application_data;
  abfd = aux->abfd;
  sec = aux->sec;
  opb = bfd_octets_per_byte (abfd);

  /* Perform a binary search looking for the closest symbol to the
     required value.  We are searching the range (min, max].  */
  while (min + 1 < max)
    {
      asymbol *sym;

      thisplace = (max + min) / 2;
      sym = sorted_syms[thisplace];

      if (bfd_asymbol_value (sym) > vma)
	max = thisplace;
      else if (bfd_asymbol_value (sym) < vma)
	min = thisplace;
      else
	{
	  min = thisplace;
	  break;
	}
    }

  /* The symbol we want is now in min, the low end of the range we
     were searching.  If there are several symbols with the same
     value, we want the first one.  */
  thisplace = min;
  while (thisplace > 0
	 && (bfd_asymbol_value (sorted_syms[thisplace])
	     == bfd_asymbol_value (sorted_syms[thisplace - 1])))
    --thisplace;

  /* If the file is relocatable, and the symbol could be from this
     section, prefer a symbol from this section over symbols from
     others, even if the other symbol's value might be closer.

     Note that this may be wrong for some symbol references if the
     sections have overlapping memory ranges, but in that case there's
     no way to tell what's desired without looking at the relocation
     table.
     
     Also give the target a chance to reject symbols.  */
  want_section = (aux->require_sec
		  || ((abfd->flags & HAS_RELOC) != 0
		      && vma >= bfd_get_section_vma (abfd, sec)
		      && vma < (bfd_get_section_vma (abfd, sec)
				+ bfd_section_size (abfd, sec) / opb)));
  if ((sorted_syms[thisplace]->section != sec && want_section)
      || !info->symbol_is_valid (sorted_syms[thisplace], info))
    {
      long i;
      long newplace;

      for (i = thisplace + 1; i < sorted_symcount; i++)
	{
	  if (bfd_asymbol_value (sorted_syms[i])
	      != bfd_asymbol_value (sorted_syms[thisplace]))
	    break;
	}

      --i;
      newplace = sorted_symcount;

      for (; i >= 0; i--)
	{
	  if ((sorted_syms[i]->section == sec || !want_section)
	      && info->symbol_is_valid (sorted_syms[i], info))
	    {
	      if (newplace == sorted_symcount)
		newplace = i;

	      if (bfd_asymbol_value (sorted_syms[i])
		  != bfd_asymbol_value (sorted_syms[newplace]))
		break;

	      /* Remember this symbol and keep searching until we reach
		 an earlier address.  */
	      newplace = i;
	    }
	}

      if (newplace != sorted_symcount)
	thisplace = newplace;
      else
	{
	  /* We didn't find a good symbol with a smaller value.
	     Look for one with a larger value.  */
	  for (i = thisplace + 1; i < sorted_symcount; i++)
	    {
	      if ((sorted_syms[i]->section == sec || !want_section)
		  && info->symbol_is_valid (sorted_syms[i], info))
		{
		  thisplace = i;
		  break;
		}
	    }
	}

      if ((sorted_syms[thisplace]->section != sec && want_section)
	  || !info->symbol_is_valid (sorted_syms[thisplace], info))
	/* There is no suitable symbol.  */
	return NULL;
    }

  if (place != NULL)
    *place = thisplace;

  return sorted_syms[thisplace];
}