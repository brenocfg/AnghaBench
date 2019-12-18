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

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 unsigned int* buf ; 
 size_t compiledOfs ; 
 int pass ; 
 int /*<<< orphan*/  printf (char*,unsigned int*,char*,int,int,int) ; 

__attribute__((used)) static void InstImmU( char *opname, int opcode, int destReg, int aReg, int immediate ) {
	unsigned		r;
	
	if ( immediate > 0xffff || immediate < 0 ) {
		Com_Error( ERR_FATAL, "VM_Compile: immediate value %i out of range", immediate );
	}
	#if DEBUG_VM
	if(pass == 1)
		printf("\t\t\t%p %s\tr%d,r%d,0x%x\n",&buf[compiledOfs],opname,destReg,aReg,immediate);
	#endif
    r = opcode | ( destReg << 21 ) | ( aReg << 16 ) | ( immediate & 0xffff );
	buf[ compiledOfs ] = r;
	compiledOfs++;
}