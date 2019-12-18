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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  opcode ;

/* Variables and functions */
 int access_process_vm (struct task_struct*,unsigned long,unsigned long*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int insn_size(struct task_struct *child, unsigned long pc)
{
  unsigned long opcode;
  int copied;
  int opsize = 0;

  /* Read the opcode at pc (do what PTRACE_PEEKTEXT would do). */
  copied = access_process_vm(child, pc, &opcode, sizeof(opcode), 0);
  if (copied != sizeof(opcode))
    return 0;

  switch ((opcode & 0x0f00) >> 8) {
  case 0x0:
  case 0x9:
  case 0xb:
	  opsize = 2;
	  break;
  case 0xe:
  case 0xf:
	  opsize = 6;
	  break;
  case 0xd:
	  /* Could be 4 or 6; check more bits. */
	  if ((opcode & 0xff) == 0xff)
		  opsize = 4;
	  else
		  opsize = 6;
	  break;
  default:
	  panic("ERROR: Couldn't find size of opcode 0x%lx at 0x%lx\n",
		opcode, pc);
  }

  return opsize;
}