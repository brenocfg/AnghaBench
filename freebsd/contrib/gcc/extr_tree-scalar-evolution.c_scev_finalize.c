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
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  already_instantiated ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scalar_evolution_info ; 

void
scev_finalize (void)
{
  htab_delete (scalar_evolution_info);
  BITMAP_FREE (already_instantiated);
}