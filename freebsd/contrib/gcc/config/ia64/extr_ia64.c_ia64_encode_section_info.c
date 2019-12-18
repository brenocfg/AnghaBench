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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_encode_section_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ia64_encode_addr_area (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ia64_encode_section_info (tree decl, rtx rtl, int first)
{
  default_encode_section_info (decl, rtl, first);

  /* Careful not to prod global register variables.  */
  if (TREE_CODE (decl) == VAR_DECL
      && GET_CODE (DECL_RTL (decl)) == MEM
      && GET_CODE (XEXP (DECL_RTL (decl), 0)) == SYMBOL_REF
      && (TREE_STATIC (decl) || DECL_EXTERNAL (decl)))
    ia64_encode_addr_area (decl, XEXP (rtl, 0));
}