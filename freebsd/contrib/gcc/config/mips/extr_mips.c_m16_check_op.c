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
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
m16_check_op (rtx op, int low, int high, int mask)
{
  return (GET_CODE (op) == CONST_INT
	  && INTVAL (op) >= low
	  && INTVAL (op) <= high
	  && (INTVAL (op) & mask) == 0);
}