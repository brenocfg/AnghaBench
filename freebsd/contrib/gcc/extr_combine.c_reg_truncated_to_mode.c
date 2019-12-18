#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int truncated_to_mode; scalar_t__ truncation_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ TRULY_NOOP_TRUNCATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ label_tick ; 
 TYPE_1__* reg_stat ; 

__attribute__((used)) static bool
reg_truncated_to_mode (enum machine_mode mode, rtx x)
{
  enum machine_mode truncated = reg_stat[REGNO (x)].truncated_to_mode;

  if (truncated == 0 || reg_stat[REGNO (x)].truncation_label != label_tick)
    return false;
  if (GET_MODE_SIZE (truncated) <= GET_MODE_SIZE (mode))
    return true;
  if (TRULY_NOOP_TRUNCATION (GET_MODE_BITSIZE (mode),
			     GET_MODE_BITSIZE (truncated)))
    return true;
  return false;
}