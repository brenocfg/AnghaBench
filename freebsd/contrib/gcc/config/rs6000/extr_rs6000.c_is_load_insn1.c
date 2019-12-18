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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_SRC (scalar_t__) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 int is_mem_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
is_load_insn1 (rtx pat)
{
  if (!pat || pat == NULL_RTX)
    return false;

  if (GET_CODE (pat) == SET)
    return is_mem_ref (SET_SRC (pat));

  if (GET_CODE (pat) == PARALLEL)
    {
      int i;

      for (i = 0; i < XVECLEN (pat, 0); i++)
	if (is_load_insn1 (XVECEXP (pat, 0, i)))
	  return true;
    }

  return false;
}