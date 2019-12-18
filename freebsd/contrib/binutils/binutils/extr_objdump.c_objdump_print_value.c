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
struct objdump_disasm_info {int /*<<< orphan*/  abfd; } ;
struct disassemble_info {int /*<<< orphan*/  stream; int /*<<< orphan*/  (* fprintf_func ) (int /*<<< orphan*/ ,char*,char*) ;scalar_t__ application_data; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_sprintf_vma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
objdump_print_value (bfd_vma vma, struct disassemble_info *info,
		     bfd_boolean skip_zeroes)
{
  char buf[30];
  char *p;
  struct objdump_disasm_info *aux;

  aux = (struct objdump_disasm_info *) info->application_data;
  bfd_sprintf_vma (aux->abfd, buf, vma);
  if (! skip_zeroes)
    p = buf;
  else
    {
      for (p = buf; *p == '0'; ++p)
	;
      if (*p == '\0')
	--p;
    }
  (*info->fprintf_func) (info->stream, "%s", p);
}