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
 int /*<<< orphan*/ * btr_reference_found ; 
 scalar_t__ btr_referenced_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static rtx *
find_btr_use (rtx insn)
{
  return btr_referenced_p (insn, NULL) ? btr_reference_found : NULL;
}