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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ REG ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 

int
sparc_absnegfloat_split_legitimate (rtx x, rtx y)
{
  if (GET_CODE (x) != REG)
    return 0;
  if (GET_CODE (y) != REG)
    return 0;
  if (REGNO (x) == REGNO (y))
    return 0;
  return 1;
}