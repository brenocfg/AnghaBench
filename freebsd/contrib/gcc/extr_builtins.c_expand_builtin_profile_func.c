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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  BUILT_IN_RETURN_ADDRESS ; 
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCT_NORMAL ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  emit_library_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_builtin_return_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_function_entry_libfunc ; 
 int /*<<< orphan*/  profile_function_exit_libfunc ; 

__attribute__((used)) static rtx
expand_builtin_profile_func (bool exitp)
{
  rtx this, which;

  this = DECL_RTL (current_function_decl);
  gcc_assert (MEM_P (this));
  this = XEXP (this, 0);

  if (exitp)
    which = profile_function_exit_libfunc;
  else
    which = profile_function_entry_libfunc;

  emit_library_call (which, LCT_NORMAL, VOIDmode, 2, this, Pmode,
		     expand_builtin_return_addr (BUILT_IN_RETURN_ADDRESS,
						 0),
		     Pmode);

  return const0_rtx;
}