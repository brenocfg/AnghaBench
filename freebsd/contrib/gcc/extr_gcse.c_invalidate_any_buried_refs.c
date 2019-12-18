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
struct ls_expr {int invalid; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int /*<<< orphan*/ ) ; 
 int GET_RTX_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 struct ls_expr* ldst_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ simple_mem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
invalidate_any_buried_refs (rtx x)
{
  const char * fmt;
  int i, j;
  struct ls_expr * ptr;

  /* Invalidate it in the list.  */
  if (MEM_P (x) && simple_mem (x))
    {
      ptr = ldst_entry (x);
      ptr->invalid = 1;
    }

  /* Recursively process the insn.  */
  fmt = GET_RTX_FORMAT (GET_CODE (x));

  for (i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	invalidate_any_buried_refs (XEXP (x, i));
      else if (fmt[i] == 'E')
	for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	  invalidate_any_buried_refs (XVECEXP (x, i, j));
    }
}