#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * output_anchor; } ;
struct TYPE_4__ {scalar_t__ min_anchor_offset; scalar_t__ max_anchor_offset; TYPE_1__ asm_out; } ;

/* Variables and functions */
 TYPE_2__ targetm ; 

__attribute__((used)) static bool
target_supports_section_anchors_p (void)
{
  if (targetm.min_anchor_offset == 0 && targetm.max_anchor_offset == 0)
    return false;

  if (targetm.asm_out.output_anchor == NULL)
    return false;

  return true;
}