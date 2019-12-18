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
struct spu_elf_stack_info {int max_fun; } ;
struct function_info {int dummy; } ;
struct _spu_elf_section_data {struct spu_elf_stack_info* stack_info; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 struct spu_elf_stack_info* bfd_zmalloc (int) ; 
 struct _spu_elf_section_data* spu_elf_section_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct spu_elf_stack_info *
alloc_stack_info (asection *sec, int max_fun)
{
  struct _spu_elf_section_data *sec_data = spu_elf_section_data (sec);
  bfd_size_type amt;

  amt = sizeof (struct spu_elf_stack_info);
  amt += (max_fun - 1) * sizeof (struct function_info);
  sec_data->stack_info = bfd_zmalloc (amt);
  if (sec_data->stack_info != NULL)
    sec_data->stack_info->max_fun = max_fun;
  return sec_data->stack_info;
}