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
struct TYPE_3__ {unsigned int pc; unsigned int type; int address_mask; scalar_t__ ir; int /*<<< orphan*/ * inst; } ;
typedef  TYPE_1__ m68k_info ;
typedef  int /*<<< orphan*/  MCInst ;

/* Variables and functions */
#define  M68K_CPU_TYPE_68000 133 
#define  M68K_CPU_TYPE_68010 132 
#define  M68K_CPU_TYPE_68020 131 
#define  M68K_CPU_TYPE_68030 130 
#define  M68K_CPU_TYPE_68040 129 
#define  M68K_CPU_TYPE_68EC020 128 
 int TYPE_68000 ; 
 int TYPE_68010 ; 
 void* TYPE_68020 ; 
 int TYPE_68030 ; 
 int TYPE_68040 ; 

__attribute__((used)) static void m68k_setup_internals(m68k_info* info, MCInst* inst, unsigned int pc, unsigned int cpu_type)
{
	info->inst = inst;
	info->pc = pc;
	info->ir = 0;
	info->type = cpu_type;
	info->address_mask = 0xffffffff;

	switch(info->type) {
		case M68K_CPU_TYPE_68000:
			info->type = TYPE_68000;
			info->address_mask = 0x00ffffff;
			break;
		case M68K_CPU_TYPE_68010:
			info->type = TYPE_68010;
			info->address_mask = 0x00ffffff;
			break;
		case M68K_CPU_TYPE_68EC020:
			info->type = TYPE_68020;
			info->address_mask = 0x00ffffff;
			break;
		case M68K_CPU_TYPE_68020:
			info->type = TYPE_68020;
			info->address_mask = 0xffffffff;
			break;
		case M68K_CPU_TYPE_68030:
			info->type = TYPE_68030;
			info->address_mask = 0xffffffff;
			break;
		case M68K_CPU_TYPE_68040:
			info->type = TYPE_68040;
			info->address_mask = 0xffffffff;
			break;
		default:
			info->address_mask = 0;
			return;
	}
}