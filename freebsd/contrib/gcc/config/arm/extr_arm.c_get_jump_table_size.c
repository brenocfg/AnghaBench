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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ ADDR_DIFF_VEC ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ JUMP_TABLES_IN_TEXT_SECTION ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ readonly_data_section ; 
 scalar_t__ text_section ; 

__attribute__((used)) static HOST_WIDE_INT
get_jump_table_size (rtx insn)
{
  /* ADDR_VECs only take room if read-only data does into the text
     section.  */
  if (JUMP_TABLES_IN_TEXT_SECTION || readonly_data_section == text_section)
    {
      rtx body = PATTERN (insn);
      int elt = GET_CODE (body) == ADDR_DIFF_VEC ? 1 : 0;

      return GET_MODE_SIZE (GET_MODE (body)) * XVECLEN (body, elt);
    }

  return 0;
}