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
 scalar_t__ COND_VC () ; 
 int /*<<< orphan*/  EXCEPTION_TRAPV ; 
 int /*<<< orphan*/  m68ki_exception_trap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68k_op_trapv(void)
{
  if(COND_VC())
  {
    return;
  }
  m68ki_exception_trap(EXCEPTION_TRAPV);  /* HJB 990403 */
}