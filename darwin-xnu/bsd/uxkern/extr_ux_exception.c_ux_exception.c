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
typedef  int /*<<< orphan*/  mach_exception_subcode_t ;
typedef  int /*<<< orphan*/  mach_exception_code_t ;

/* Variables and functions */
#define  EXC_ARITHMETIC 137 
#define  EXC_BAD_ACCESS 136 
#define  EXC_BAD_INSTRUCTION 135 
#define  EXC_BREAKPOINT 134 
#define  EXC_EMULATION 133 
#define  EXC_SOFTWARE 132 
#define  EXC_SOFT_SIGNAL 131 
#define  EXC_UNIX_ABORT 130 
#define  EXC_UNIX_BAD_PIPE 129 
#define  EXC_UNIX_BAD_SYSCALL 128 
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int SIGABRT ; 
 int SIGBUS ; 
 int SIGEMT ; 
 int SIGFPE ; 
 int SIGILL ; 
 int SIGKILL ; 
 int SIGPIPE ; 
 int SIGSEGV ; 
 int SIGSYS ; 
 int SIGTRAP ; 
 int machine_exception (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ux_exception(int                        exception,
             mach_exception_code_t      code,
             mach_exception_subcode_t   subcode)
{
	int machine_signal = 0;

	/* Try machine-dependent translation first. */
	if ((machine_signal = machine_exception(exception, code, subcode)) != 0)
		return machine_signal;

	switch(exception) {
		case EXC_BAD_ACCESS:
			if (code == KERN_INVALID_ADDRESS)
				return SIGSEGV;
			else
				return SIGBUS;

		case EXC_BAD_INSTRUCTION:
			return SIGILL;

		case EXC_ARITHMETIC:
			return SIGFPE;

		case EXC_EMULATION:
			return SIGEMT;

		case EXC_SOFTWARE:
			switch (code) {
				case EXC_UNIX_BAD_SYSCALL:
					return SIGSYS;
				case EXC_UNIX_BAD_PIPE:
					return SIGPIPE;
				case EXC_UNIX_ABORT:
					return SIGABRT;
				case EXC_SOFT_SIGNAL:
					return SIGKILL;
			}
			break;

		case EXC_BREAKPOINT:
			return SIGTRAP;
	}

	return 0;
}