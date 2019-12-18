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
 int /*<<< orphan*/  TDI_cgraph ; 
 int /*<<< orphan*/  cgraph_dump_file ; 
 int /*<<< orphan*/  dump_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
init_cgraph (void)
{
  cgraph_dump_file = dump_begin (TDI_cgraph, NULL);
}