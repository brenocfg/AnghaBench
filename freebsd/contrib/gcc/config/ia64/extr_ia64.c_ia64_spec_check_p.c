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
 scalar_t__ COND_EXEC ; 
 int /*<<< orphan*/  COND_EXEC_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int ia64_spec_check_src_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ia64_spec_check_p (rtx x)
{
  x = PATTERN (x);
  if (GET_CODE (x) == COND_EXEC)
    x = COND_EXEC_CODE (x);
  if (GET_CODE (x) == SET)
    return ia64_spec_check_src_p (SET_SRC (x));
  return 0;
}