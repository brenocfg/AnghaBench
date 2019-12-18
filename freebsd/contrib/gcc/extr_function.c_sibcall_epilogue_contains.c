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
 int contains (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ sibcall_epilogue ; 

int
sibcall_epilogue_contains (rtx insn)
{
  if (sibcall_epilogue)
    return contains (insn, &sibcall_epilogue);
  return 0;
}