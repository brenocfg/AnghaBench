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
 int /*<<< orphan*/  add_setshow_boolean_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  coerce_float_to_double_p ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  unwind_on_signal_p ; 

void
_initialize_infcall (void)
{
  add_setshow_boolean_cmd ("coerce-float-to-double", class_obscure,
			   &coerce_float_to_double_p, "\
Set coercion of floats to doubles when calling functions\n\
Variables of type float should generally be converted to doubles before\n\
calling an unprototyped function, and left alone when calling a prototyped\n\
function.  However, some older debug info formats do not provide enough\n\
information to determine that a function is prototyped.  If this flag is\n\
set, GDB will perform the conversion for a function it considers\n\
unprototyped.\n\
The default is to perform the conversion.\n", "\
Show coercion of floats to doubles when calling functions\n\
Variables of type float should generally be converted to doubles before\n\
calling an unprototyped function, and left alone when calling a prototyped\n\
function.  However, some older debug info formats do not provide enough\n\
information to determine that a function is prototyped.  If this flag is\n\
set, GDB will perform the conversion for a function it considers\n\
unprototyped.\n\
The default is to perform the conversion.\n",
			   NULL, NULL, &setlist, &showlist);

  add_setshow_boolean_cmd ("unwindonsignal", no_class,
			   &unwind_on_signal_p, "\
Set unwinding of stack if a signal is received while in a call dummy.\n\
The unwindonsignal lets the user determine what gdb should do if a signal\n\
is received while in a function called from gdb (call dummy).  If set, gdb\n\
unwinds the stack and restore the context to what as it was before the call.\n\
The default is to stop in the frame where the signal was received.", "\
Set unwinding of stack if a signal is received while in a call dummy.\n\
The unwindonsignal lets the user determine what gdb should do if a signal\n\
is received while in a function called from gdb (call dummy).  If set, gdb\n\
unwinds the stack and restore the context to what as it was before the call.\n\
The default is to stop in the frame where the signal was received.",
			   NULL, NULL, &setlist, &showlist);
}