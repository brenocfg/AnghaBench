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
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ UNSPEC ; 
#define  UNSPEC_DEF_CFA 129 
#define  UNSPEC_REG_SAVE 128 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2out_def_cfa (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2out_reg_save_reg (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static void
ix86_dwarf_handle_frame_unspec (const char *label, rtx pattern, int index)
{
  rtx unspec = SET_SRC (pattern);
  gcc_assert (GET_CODE (unspec) == UNSPEC);

  switch (index)
    {
    case UNSPEC_REG_SAVE:
      dwarf2out_reg_save_reg (label, XVECEXP (unspec, 0, 0),
			      SET_DEST (pattern));
      break;
    case UNSPEC_DEF_CFA:
      dwarf2out_def_cfa (label, REGNO (SET_DEST (pattern)),
			 INTVAL (XVECEXP (unspec, 0, 0)));
      break;
    default:
      gcc_unreachable ();
    }
}