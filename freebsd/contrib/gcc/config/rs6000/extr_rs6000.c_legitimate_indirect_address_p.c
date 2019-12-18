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
 scalar_t__ INT_REG_OK_FOR_BASE_P (int /*<<< orphan*/ ,int) ; 
 scalar_t__ REG ; 

inline bool
legitimate_indirect_address_p (rtx x, int strict)
{
  return GET_CODE (x) == REG && INT_REG_OK_FOR_BASE_P (x, strict);
}