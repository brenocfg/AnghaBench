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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  for_each_eh_label (int /*<<< orphan*/ ) ; 
 scalar_t__ forced_labels ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_labels ; 
 int /*<<< orphan*/  offsets_known_at ; 
 int /*<<< orphan*/  set_initial_eh_label_offset ; 
 int /*<<< orphan*/  set_label_offsets (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_initial_label_offsets (void)
{
  rtx x;
  memset (offsets_known_at, 0, num_labels);

  for (x = forced_labels; x; x = XEXP (x, 1))
    if (XEXP (x, 0))
      set_label_offsets (XEXP (x, 0), NULL_RTX, 1);

  for_each_eh_label (set_initial_eh_label_offset);
}