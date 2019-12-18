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
 size_t FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int /*<<< orphan*/ ) ; 
 int GET_RTX_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__* reg_equiv_memory_loc ; 

__attribute__((used)) static int
refers_to_mem_for_reload_p (rtx x)
{
  const char *fmt;
  int i;

  if (MEM_P (x))
    return 1;

  if (REG_P (x))
    return (REGNO (x) >= FIRST_PSEUDO_REGISTER
	    && reg_equiv_memory_loc[REGNO (x)]);

  fmt = GET_RTX_FORMAT (GET_CODE (x));
  for (i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
    if (fmt[i] == 'e'
	&& (MEM_P (XEXP (x, i))
	    || refers_to_mem_for_reload_p (XEXP (x, i))))
      return 1;

  return 0;
}