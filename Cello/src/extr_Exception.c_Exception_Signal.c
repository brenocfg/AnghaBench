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
 int /*<<< orphan*/  DivisionByZeroError ; 
 int /*<<< orphan*/  IllegalInstructionError ; 
 int /*<<< orphan*/  ProgramAbortedError ; 
 int /*<<< orphan*/  ProgramInterruptedError ; 
 int /*<<< orphan*/  ProgramTerminationError ; 
#define  SIGABRT 133 
#define  SIGFPE 132 
#define  SIGILL 131 
#define  SIGINT 130 
#define  SIGSEGV 129 
#define  SIGTERM 128 
 int /*<<< orphan*/  SegmentationError ; 
 int /*<<< orphan*/  throw (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void Exception_Signal(int sig) {
  switch(sig) {
    case SIGABRT: throw(ProgramAbortedError, "Program Aborted");
    case SIGFPE:  throw(DivisionByZeroError, "Division by Zero");
    case SIGILL:  throw(IllegalInstructionError, "Illegal Instruction");
    case SIGINT:  throw(ProgramInterruptedError, "Program Interrupted");
    case SIGSEGV: throw(SegmentationError, "Segmentation fault");
    case SIGTERM: throw(ProgramTerminationError, "Program Terminated");
  }
}