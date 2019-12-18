#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_5__ {int dt_oflags; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_6__ {int r_offset; int /*<<< orphan*/  r_info; } ;
typedef  TYPE_2__ GElf_Rela ;

/* Variables and functions */
 int DTRACE_O_LP64 ; 
 scalar_t__ DT_OP_CALL ; 
 scalar_t__ DT_OP_JMP32 ; 
 scalar_t__ DT_OP_NOP ; 
 scalar_t__ DT_OP_RET ; 
 scalar_t__ DT_OP_REX_RAX ; 
 scalar_t__ DT_OP_XOR_EAX_0 ; 
 scalar_t__ DT_OP_XOR_EAX_1 ; 
 scalar_t__ GELF_R_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ R_386_PC32 ; 
 scalar_t__ R_386_PLT32 ; 
 int /*<<< orphan*/  dt_dprintf (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_modtext(dtrace_hdl_t *dtp, char *p, int isenabled, GElf_Rela *rela,
    uint32_t *off)
{
	uint8_t *ip = (uint8_t *)(p + rela->r_offset - 1);
	uint8_t ret;

	/*
	 * On x86, the first byte of the instruction is the call opcode and
	 * the next four bytes are the 32-bit address; the relocation is for
	 * the address operand. We back up the offset to the first byte of
	 * the instruction. For is-enabled probes, we later advance the offset
	 * so that it hits the first nop in the instruction sequence.
	 */
	(*off) -= 1;

	/*
	 * We only know about some specific relocation types. Luckily
	 * these types have the same values on both 32-bit and 64-bit
	 * x86 architectures.
	 */
	if (GELF_R_TYPE(rela->r_info) != R_386_PC32 &&
	    GELF_R_TYPE(rela->r_info) != R_386_PLT32)
		return (-1);

	/*
	 * We may have already processed this object file in an earlier linker
	 * invocation. Check to see if the present instruction sequence matches
	 * the one we would install. For is-enabled probes, we advance the
	 * offset to the first nop instruction in the sequence to match the
	 * text modification code below.
	 */
	if (!isenabled) {
		if ((ip[0] == DT_OP_NOP || ip[0] == DT_OP_RET) &&
		    ip[1] == DT_OP_NOP && ip[2] == DT_OP_NOP &&
		    ip[3] == DT_OP_NOP && ip[4] == DT_OP_NOP)
			return (0);
	} else if (dtp->dt_oflags & DTRACE_O_LP64) {
		if (ip[0] == DT_OP_REX_RAX &&
		    ip[1] == DT_OP_XOR_EAX_0 && ip[2] == DT_OP_XOR_EAX_1 &&
		    (ip[3] == DT_OP_NOP || ip[3] == DT_OP_RET) &&
		    ip[4] == DT_OP_NOP) {
			(*off) += 3;
			return (0);
		}
	} else {
		if (ip[0] == DT_OP_XOR_EAX_0 && ip[1] == DT_OP_XOR_EAX_1 &&
		    (ip[2] == DT_OP_NOP || ip[2] == DT_OP_RET) &&
		    ip[3] == DT_OP_NOP && ip[4] == DT_OP_NOP) {
			(*off) += 2;
			return (0);
		}
	}

	/*
	 * We expect either a call instrution with a 32-bit displacement or a
	 * jmp instruction with a 32-bit displacement acting as a tail-call.
	 */
	if (ip[0] != DT_OP_CALL && ip[0] != DT_OP_JMP32) {
		dt_dprintf("found %x instead of a call or jmp instruction at "
		    "%llx\n", ip[0], (u_longlong_t)rela->r_offset);
		return (-1);
	}

	ret = (ip[0] == DT_OP_JMP32) ? DT_OP_RET : DT_OP_NOP;

	/*
	 * Establish the instruction sequence -- all nops for probes, and an
	 * instruction to clear the return value register (%eax/%rax) followed
	 * by nops for is-enabled probes. For is-enabled probes, we advance
	 * the offset to the first nop. This isn't stricly necessary but makes
	 * for more readable disassembly when the probe is enabled.
	 */
	if (!isenabled) {
		ip[0] = ret;
		ip[1] = DT_OP_NOP;
		ip[2] = DT_OP_NOP;
		ip[3] = DT_OP_NOP;
		ip[4] = DT_OP_NOP;
	} else if (dtp->dt_oflags & DTRACE_O_LP64) {
		ip[0] = DT_OP_REX_RAX;
		ip[1] = DT_OP_XOR_EAX_0;
		ip[2] = DT_OP_XOR_EAX_1;
		ip[3] = ret;
		ip[4] = DT_OP_NOP;
		(*off) += 3;
	} else {
		ip[0] = DT_OP_XOR_EAX_0;
		ip[1] = DT_OP_XOR_EAX_1;
		ip[2] = ret;
		ip[3] = DT_OP_NOP;
		ip[4] = DT_OP_NOP;
		(*off) += 2;
	}

	return (0);
}