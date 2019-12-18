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
struct disassemble_info {int dummy; } ;
typedef  scalar_t__ bfd_vma ;

/* Variables and functions */
 char* lookup_name (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dis_asm_print_address(bfd_vma addr, struct disassemble_info *info)
{
  const char *name;

  printf("%08x", (int)addr);

  name = lookup_name(addr);
  if (name != NULL)
    printf(" <%s>", name);
}