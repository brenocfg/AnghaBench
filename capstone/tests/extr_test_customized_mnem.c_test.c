#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  csh ;
struct TYPE_2__ {char* member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ cs_opt_mnem ;
typedef  int cs_err ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ARCH_X86 ; 
 int /*<<< orphan*/  CS_MODE_32 ; 
 int /*<<< orphan*/  CS_OPT_MNEMONIC ; 
 int /*<<< orphan*/  X86_INS_JNE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  cs_close (int /*<<< orphan*/ *) ; 
 int cs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  print_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void test()
{
	csh handle;
	cs_err err;
	// Customize mnemonic JNE to "jnz"
	cs_opt_mnem my_mnem = { X86_INS_JNE, "jnz" };
	// Set .mnemonic to NULL to reset to default mnemonic
	cs_opt_mnem default_mnem = { X86_INS_JNE, NULL };

	err = cs_open(CS_ARCH_X86, CS_MODE_32, &handle);
	if (err) {
		printf("Failed on cs_open() with error returned: %u\n", err);
		abort();
	}

	// 1. Print out the instruction in default setup.
	printf("Disassemble X86 code with default instruction mnemonic\n");
	print_insn(handle);

	// Customized mnemonic JNE to JNZ using CS_OPT_MNEMONIC option
	printf("\nNow customize engine to change mnemonic from 'JNE' to 'JNZ'\n");
	cs_option(handle, CS_OPT_MNEMONIC, (size_t)&my_mnem);

	// 2. Now print out the instruction in newly customized setup.
	print_insn(handle);

	// Reset engine to use the default mnemonic of JNE
	printf("\nReset engine to use the default mnemonic\n");
	cs_option(handle, CS_OPT_MNEMONIC, (size_t)&default_mnem);

	// 3. Now print out the instruction in default setup.
	print_insn(handle);

	// Done
	cs_close(&handle);
}