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
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_V9 ; 

int
registers_ok_for_ldd_peep (rtx reg1, rtx reg2)
{
  /* We might have been passed a SUBREG.  */
  if (GET_CODE (reg1) != REG || GET_CODE (reg2) != REG) 
    return 0;

  if (REGNO (reg1) % 2 != 0)
    return 0;

  /* Integer ldd is deprecated in SPARC V9 */ 
  if (TARGET_V9 && REGNO (reg1) < 32)                  
    return 0;                             

  return (REGNO (reg1) == REGNO (reg2) - 1);
}