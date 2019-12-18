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
struct propagate_block_info {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_RTX_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ RTX_AUTOINC ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_mems_from_set (struct propagate_block_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
invalidate_mems_from_autoinc (rtx *px, void *data)
{
  rtx x = *px;
  struct propagate_block_info *pbi = data;

  if (GET_RTX_CLASS (GET_CODE (x)) == RTX_AUTOINC)
    {
      invalidate_mems_from_set (pbi, XEXP (x, 0));
      return -1;
    }

  return 0;
}