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
struct table_elt {int /*<<< orphan*/  exp; struct table_elt* next_same_value; struct table_elt* first_same_value; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int CONST_INT ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_HASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ exp_equiv_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct table_elt* lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  word_mode ; 

__attribute__((used)) static rtx
lookup_as_function (rtx x, enum rtx_code code)
{
  struct table_elt *p
    = lookup (x, SAFE_HASH (x, VOIDmode), GET_MODE (x));

  /* If we are looking for a CONST_INT, the mode doesn't really matter, as
     long as we are narrowing.  So if we looked in vain for a mode narrower
     than word_mode before, look for word_mode now.  */
  if (p == 0 && code == CONST_INT
      && GET_MODE_SIZE (GET_MODE (x)) < GET_MODE_SIZE (word_mode))
    {
      x = copy_rtx (x);
      PUT_MODE (x, word_mode);
      p = lookup (x, SAFE_HASH (x, VOIDmode), word_mode);
    }

  if (p == 0)
    return 0;

  for (p = p->first_same_value; p; p = p->next_same_value)
    if (GET_CODE (p->exp) == code
	/* Make sure this is a valid entry in the table.  */
	&& exp_equiv_p (p->exp, p->exp, 1, false))
      return p->exp;

  return 0;
}