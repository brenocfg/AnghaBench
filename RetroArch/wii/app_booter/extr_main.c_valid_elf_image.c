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
typedef  int int32_t ;
struct TYPE_3__ {scalar_t__ e_type; scalar_t__ e_machine; } ;
typedef  TYPE_1__ Elf32_Ehdr ;

/* Variables and functions */
 scalar_t__ EM_PPC ; 
 scalar_t__ ET_EXEC ; 
 int /*<<< orphan*/  IS_ELF (TYPE_1__) ; 

__attribute__((used)) static int32_t valid_elf_image (void *addr)
{
   Elf32_Ehdr *ehdr = (Elf32_Ehdr*)addr;

   if (!IS_ELF (*ehdr))
      return 0;

   if (ehdr->e_type != ET_EXEC)
      return -1;

   if (ehdr->e_machine != EM_PPC)
      return -1;

   return 1;
}