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
 scalar_t__ TARGET_MMX ; 
 int /*<<< orphan*/  ix86_init_mmx_sse_builtins () ; 

__attribute__((used)) static void
ix86_init_builtins (void)
{
  if (TARGET_MMX)
    ix86_init_mmx_sse_builtins ();
}