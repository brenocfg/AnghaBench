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
typedef  scalar_t__ wordU ;
struct disassemble_info {int (* read_memory_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct disassemble_info*) ;} ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 scalar_t__ bfd_getl16 (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 

__attribute__((used)) static wordU
get_word_at_PC (bfd_vma memaddr, struct disassemble_info *info)
{
  bfd_byte buffer[4];
  int status;
  wordU insn = 0;

  status = info->read_memory_func (memaddr, buffer, 2, info);

  if (status == 0)
    insn = (wordU) bfd_getl16 (buffer);

  return insn;
}