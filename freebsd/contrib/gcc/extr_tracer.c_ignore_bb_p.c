#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {scalar_t__ index; } ;

/* Variables and functions */
 scalar_t__ NUM_FIXED_BLOCKS ; 
 int /*<<< orphan*/  maybe_hot_bb_p (TYPE_1__*) ; 

__attribute__((used)) static bool
ignore_bb_p (basic_block bb)
{
  if (bb->index < NUM_FIXED_BLOCKS)
    return true;
  if (!maybe_hot_bb_p (bb))
    return true;
  return false;
}