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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ SYMBOL_REF ; 
 int /*<<< orphan*/  VOIDmode ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_identifier (char const*) ; 

rtx
rs6000_longcall_ref (rtx call_ref)
{
  const char *call_name;
  tree node;

  if (GET_CODE (call_ref) != SYMBOL_REF)
    return call_ref;

  /* System V adds '.' to the internal name, so skip them.  */
  call_name = XSTR (call_ref, 0);
  if (*call_name == '.')
    {
      while (*call_name == '.')
	call_name++;

      node = get_identifier (call_name);
      call_ref = gen_rtx_SYMBOL_REF (VOIDmode, IDENTIFIER_POINTER (node));
    }

  return force_reg (Pmode, call_ref);
}