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
struct disassemble_info {int /*<<< orphan*/  (* fprintf_func ) (void*,char*,char*) ;void* stream; } ;
typedef  int /*<<< orphan*/  (* fprintf_ftype ) (void*,char*,char*) ;

/* Variables and functions */

__attribute__((used)) static void
print_insn_parallel_sym (struct disassemble_info *info)
{
  void *stream = info->stream;
  fprintf_ftype func = info->fprintf_func;

  /* 10:       0000            nop!
     4 space + 1 colon + 1 space + 1 tab + 8 opcode + 2 space + 1 tab.
     FIXME: the space number is not accurate.  */
  func (stream, "%s", " ||\n      \t          \t");
}