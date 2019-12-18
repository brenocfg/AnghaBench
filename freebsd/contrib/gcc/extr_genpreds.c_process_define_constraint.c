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
 scalar_t__ DEFINE_ADDRESS_CONSTRAINT ; 
 scalar_t__ DEFINE_MEMORY_CONSTRAINT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_constraint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
process_define_constraint (rtx c, int lineno)
{
  add_constraint (XSTR (c, 0), 0, XEXP (c, 2),
		  GET_CODE (c) == DEFINE_MEMORY_CONSTRAINT,
		  GET_CODE (c) == DEFINE_ADDRESS_CONSTRAINT,
		  lineno);
}