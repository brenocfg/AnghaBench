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
 scalar_t__ BITS_PER_WORD ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_BITSIZE (int /*<<< orphan*/ ) ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
verify_wide_reg_1 (rtx *px, void *pregno)
{
  rtx x = *px;
  unsigned int regno = *(int *) pregno;

  if (REG_P (x) && REGNO (x) == regno)
    {
      if (GET_MODE_BITSIZE (GET_MODE (x)) <= BITS_PER_WORD)
	return 2;
      return 1;
    }
  return 0;
}