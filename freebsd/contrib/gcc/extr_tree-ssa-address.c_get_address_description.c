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
typedef  int /*<<< orphan*/  tree ;
struct mem_address {int /*<<< orphan*/  offset; int /*<<< orphan*/  step; int /*<<< orphan*/  index; int /*<<< orphan*/  base; int /*<<< orphan*/  symbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMR_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMR_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMR_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMR_STEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMR_SYMBOL (int /*<<< orphan*/ ) ; 

void
get_address_description (tree op, struct mem_address *addr)
{
  addr->symbol = TMR_SYMBOL (op);
  addr->base = TMR_BASE (op);
  addr->index = TMR_INDEX (op);
  addr->step = TMR_STEP (op);
  addr->offset = TMR_OFFSET (op);
}