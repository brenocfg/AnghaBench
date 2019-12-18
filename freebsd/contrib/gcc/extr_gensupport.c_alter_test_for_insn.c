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
struct queue_elem {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int) ; 
 char const* join_c_conditions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
alter_test_for_insn (struct queue_elem *ce_elem,
		     struct queue_elem *insn_elem)
{
  return join_c_conditions (XSTR (ce_elem->data, 1),
			    XSTR (insn_elem->data, 2));
}