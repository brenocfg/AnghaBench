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
 scalar_t__ LABEL_REF ; 
 scalar_t__ MINUS ; 
 scalar_t__ SYMBOL_REF ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static bool
darwin_local_data_pic (rtx disp)
{
  if (GET_CODE (disp) == MINUS)
    {
      if (GET_CODE (XEXP (disp, 0)) == LABEL_REF
          || GET_CODE (XEXP (disp, 0)) == SYMBOL_REF)
        if (GET_CODE (XEXP (disp, 1)) == SYMBOL_REF)
          {
            const char *sym_name = XSTR (XEXP (disp, 1), 0);
            if (! strcmp (sym_name, "<pic base>"))
              return true;
          }
    }

  return false;
}