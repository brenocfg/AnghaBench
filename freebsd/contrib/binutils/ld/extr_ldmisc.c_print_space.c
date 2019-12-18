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
struct TYPE_2__ {int /*<<< orphan*/  map_file; } ;

/* Variables and functions */
 TYPE_1__ config ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 

void
print_space (void)
{
  fprintf (config.map_file, " ");
}