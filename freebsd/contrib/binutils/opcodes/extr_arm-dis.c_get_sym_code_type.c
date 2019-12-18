#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct disassemble_info {int /*<<< orphan*/ * symtab; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;
struct TYPE_3__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_4__ {TYPE_1__ internal_elf_sym; } ;
typedef  TYPE_2__ elf_symbol_type ;

/* Variables and functions */
 unsigned int ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int MAP_ARM ; 
 int MAP_DATA ; 
 int MAP_THUMB ; 
 unsigned int STT_ARM_TFUNC ; 
 unsigned int STT_FUNC ; 
 int TRUE ; 
 char* bfd_asymbol_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_sym_code_type (struct disassemble_info *info, int n,
		   enum map_type *map_type)
{
  elf_symbol_type *es;
  unsigned int type;
  const char *name;

  es = *(elf_symbol_type **)(info->symtab + n);
  type = ELF_ST_TYPE (es->internal_elf_sym.st_info);

  /* If the symbol has function type then use that.  */
  if (type == STT_FUNC || type == STT_ARM_TFUNC)
    {
      *map_type = (type == STT_ARM_TFUNC) ? MAP_THUMB : MAP_ARM;
      return TRUE;
    }

  /* Check for mapping symbols.  */
  name = bfd_asymbol_name(info->symtab[n]);
  if (name[0] == '$' && (name[1] == 'a' || name[1] == 't' || name[1] == 'd')
      && (name[2] == 0 || name[2] == '.'))
    {
      *map_type = ((name[1] == 'a') ? MAP_ARM
		   : (name[1] == 't') ? MAP_THUMB
		   : MAP_DATA);
      return TRUE;
    }

  return FALSE;
}