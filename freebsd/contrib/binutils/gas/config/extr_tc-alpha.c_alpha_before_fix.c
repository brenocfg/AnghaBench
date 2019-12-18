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
 int /*<<< orphan*/  alpha_adjust_relocs ; 
 scalar_t__ alpha_literal_hash ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdoutput ; 

void
alpha_before_fix (void)
{
  if (alpha_literal_hash)
    bfd_map_over_sections (stdoutput, alpha_adjust_relocs, NULL);
}