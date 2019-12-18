#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ Elf_Internal_Sym ;

/* Variables and functions */
 int ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
#define  STT_ARM_16BIT 129 
#define  STT_ARM_TFUNC 128 
 int STT_OBJECT ; 
 int STT_TLS ; 

__attribute__((used)) static int
elf32_arm_get_symbol_type (Elf_Internal_Sym * elf_sym, int type)
{
  switch (ELF_ST_TYPE (elf_sym->st_info))
    {
    case STT_ARM_TFUNC:
      return ELF_ST_TYPE (elf_sym->st_info);

    case STT_ARM_16BIT:
      /* If the symbol is not an object, return the STT_ARM_16BIT flag.
	 This allows us to distinguish between data used by Thumb instructions
	 and non-data (which is probably code) inside Thumb regions of an
	 executable.  */
      if (type != STT_OBJECT && type != STT_TLS)
	return ELF_ST_TYPE (elf_sym->st_info);
      break;

    default:
      break;
    }

  return type;
}