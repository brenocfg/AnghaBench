#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct extended_symbol_info {TYPE_4__* elfinfo; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {TYPE_2__* section; } ;
struct TYPE_5__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_8__ {TYPE_3__ symbol; TYPE_1__ internal_elf_sym; } ;
struct TYPE_6__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYM_NAME (struct extended_symbol_info*) ; 
 scalar_t__ SYM_SIZE (struct extended_symbol_info*) ; 
 int /*<<< orphan*/  SYM_STAB_DESC (struct extended_symbol_info*) ; 
 char* SYM_STAB_NAME (struct extended_symbol_info*) ; 
 char SYM_TYPE (struct extended_symbol_info*) ; 
 scalar_t__ SYM_VALUE (struct extended_symbol_info*) ; 
 scalar_t__ bfd_is_undefined_symclass (char) ; 
 char* desc_format ; 
 char* get_symbol_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_symname (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int print_width ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_symbol_info_sysv (struct extended_symbol_info *info, bfd *abfd)
{
  print_symname ("%-20s|", SYM_NAME (info), abfd);

  if (bfd_is_undefined_symclass (SYM_TYPE (info)))
    {
      if (print_width == 32)
	printf ("        ");
      else
	printf ("                ");
    }
  else
    print_value (abfd, SYM_VALUE (info));

  printf ("|   %c  |", SYM_TYPE (info));

  if (SYM_TYPE (info) == '-')
    {
      /* A stab.  */
      printf ("%18s|  ", SYM_STAB_NAME (info));		/* (C) Type.  */
      printf (desc_format, SYM_STAB_DESC (info));	/* Size.  */
      printf ("|     |");				/* Line, Section.  */
    }
  else
    {
      /* Type, Size, Line, Section */
      if (info->elfinfo)
	printf ("%18s|",
		get_symbol_type (ELF_ST_TYPE (info->elfinfo->internal_elf_sym.st_info)));
      else
	printf ("                  |");

      if (SYM_SIZE (info))
	print_value (abfd, SYM_SIZE (info));
      else
	{
	  if (print_width == 32)
	    printf ("        ");
	  else
	    printf ("                ");
	}

      if (info->elfinfo)
	printf("|     |%s", info->elfinfo->symbol.section->name);
      else
	printf("|     |");
    }
}