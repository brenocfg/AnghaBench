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
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ cselib_reg_set_mode (int /*<<< orphan*/ ) ; 
 int rtx_equal_for_cselib_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reload_cse_noop_set_p (rtx set)
{
  if (cselib_reg_set_mode (SET_DEST (set)) != GET_MODE (SET_DEST (set)))
    return 0;

  return rtx_equal_for_cselib_p (SET_DEST (set), SET_SRC (set));
}