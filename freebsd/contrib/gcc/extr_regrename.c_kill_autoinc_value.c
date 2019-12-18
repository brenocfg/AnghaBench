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
struct value_data {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_RTX_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ RTX_AUTOINC ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_value (int /*<<< orphan*/ ,struct value_data*) ; 
 int /*<<< orphan*/  set_value_regno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct value_data*) ; 

__attribute__((used)) static int
kill_autoinc_value (rtx *px, void *data)
{
  rtx x = *px;
  struct value_data *vd = data;

  if (GET_RTX_CLASS (GET_CODE (x)) == RTX_AUTOINC)
    {
      x = XEXP (x, 0);
      kill_value (x, vd);
      set_value_regno (REGNO (x), Pmode, vd);
      return -1;
    }

  return 0;
}