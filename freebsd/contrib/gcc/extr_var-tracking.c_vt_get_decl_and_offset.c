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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MEM_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_ATTRS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_EXPR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_ATTRS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_EXPR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
vt_get_decl_and_offset (rtx rtl, tree *declp, HOST_WIDE_INT *offsetp)
{
  if (REG_P (rtl))
    {
      if (REG_ATTRS (rtl))
	{
	  *declp = REG_EXPR (rtl);
	  *offsetp = REG_OFFSET (rtl);
	  return true;
	}
    }
  else if (MEM_P (rtl))
    {
      if (MEM_ATTRS (rtl))
	{
	  *declp = MEM_EXPR (rtl);
	  *offsetp = INT_MEM_OFFSET (rtl);
	  return true;
	}
    }
  return false;
}