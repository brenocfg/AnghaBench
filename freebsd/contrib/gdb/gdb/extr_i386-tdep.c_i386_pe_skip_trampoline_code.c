#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct minimal_symbol {int dummy; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 char* SYMBOL_LINKAGE_NAME (struct minimal_symbol*) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (unsigned long) ; 
 int read_memory_unsigned_integer (unsigned long,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

CORE_ADDR
i386_pe_skip_trampoline_code (CORE_ADDR pc, char *name)
{
  if (pc && read_memory_unsigned_integer (pc, 2) == 0x25ff) /* jmp *(dest) */
    {
      unsigned long indirect = read_memory_unsigned_integer (pc + 2, 4);
      struct minimal_symbol *indsym =
	indirect ? lookup_minimal_symbol_by_pc (indirect) : 0;
      char *symname = indsym ? SYMBOL_LINKAGE_NAME (indsym) : 0;

      if (symname)
	{
	  if (strncmp (symname, "__imp_", 6) == 0
	      || strncmp (symname, "_imp_", 5) == 0)
	    return name ? 1 : read_memory_unsigned_integer (indirect, 4);
	}
    }
  return 0;			/* Not a trampoline.  */
}