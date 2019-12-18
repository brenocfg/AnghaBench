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

/* Variables and functions */
 int /*<<< orphan*/ * get_b_cc (char*) ; 
 scalar_t__ streq (char*,char*) ; 

__attribute__((used)) static int
is_bcc_insn (char * op)
{
  if (!(streq (op, "bal") || streq (op, "beq0b") || streq (op, "bnq0b")
	|| streq (op, "beq0w") || streq (op, "bnq0w")))
    if ((op[0] == 'b') && (get_b_cc (op) != NULL))
      return 1;
  return 0;
}