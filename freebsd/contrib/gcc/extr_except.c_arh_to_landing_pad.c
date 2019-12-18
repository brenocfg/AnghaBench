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
struct eh_region {int /*<<< orphan*/  landing_pad; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ alloc_INSN_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arh_to_landing_pad (struct eh_region *region, void *data)
{
  rtx *p_handlers = data;
  if (! *p_handlers)
    *p_handlers = alloc_INSN_LIST (region->landing_pad, NULL_RTX);
}