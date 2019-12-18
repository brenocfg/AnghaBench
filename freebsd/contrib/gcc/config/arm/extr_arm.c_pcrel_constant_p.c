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
 int FALSE ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MINUS ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ label_mentioned_p (int /*<<< orphan*/ ) ; 
 scalar_t__ symbol_mentioned_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcrel_constant_p (rtx x)
{
  if (GET_CODE (x) == MINUS)
    return symbol_mentioned_p (XEXP (x, 0)) && label_mentioned_p (XEXP (x, 1));

  return FALSE;
}