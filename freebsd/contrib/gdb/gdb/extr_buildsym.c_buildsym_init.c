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
 int /*<<< orphan*/ * file_symbols ; 
 int /*<<< orphan*/ * free_pendings ; 
 int /*<<< orphan*/ * global_symbols ; 
 int /*<<< orphan*/ * pending_blocks ; 
 int /*<<< orphan*/ * pending_macros ; 

void
buildsym_init (void)
{
  free_pendings = NULL;
  file_symbols = NULL;
  global_symbols = NULL;
  pending_blocks = NULL;
  pending_macros = NULL;
}