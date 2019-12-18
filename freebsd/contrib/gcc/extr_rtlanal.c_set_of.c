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
struct set_of_data {int /*<<< orphan*/  found; int /*<<< orphan*/  pat; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ INSN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct set_of_data*) ; 
 int /*<<< orphan*/  set_of_1 ; 

rtx
set_of (rtx pat, rtx insn)
{
  struct set_of_data data;
  data.found = NULL_RTX;
  data.pat = pat;
  note_stores (INSN_P (insn) ? PATTERN (insn) : insn, set_of_1, &data);
  return data.found;
}