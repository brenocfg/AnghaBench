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
 scalar_t__ CONST_DOUBLE_HIGH (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_DOUBLE_REAL_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 
 int real_identical (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
const_double_htab_eq (const void *x, const void *y)
{
  rtx a = (rtx)x, b = (rtx)y;

  if (GET_MODE (a) != GET_MODE (b))
    return 0;
  if (GET_MODE (a) == VOIDmode)
    return (CONST_DOUBLE_LOW (a) == CONST_DOUBLE_LOW (b)
	    && CONST_DOUBLE_HIGH (a) == CONST_DOUBLE_HIGH (b));
  else
    return real_identical (CONST_DOUBLE_REAL_VALUE (a),
			   CONST_DOUBLE_REAL_VALUE (b));
}