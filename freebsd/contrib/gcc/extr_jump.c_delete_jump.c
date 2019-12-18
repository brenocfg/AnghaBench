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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PC ; 
 int /*<<< orphan*/  SET_DEST (scalar_t__) ; 
 int /*<<< orphan*/  delete_computation (scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 

void
delete_jump (rtx insn)
{
  rtx set = single_set (insn);

  if (set && GET_CODE (SET_DEST (set)) == PC)
    delete_computation (insn);
}