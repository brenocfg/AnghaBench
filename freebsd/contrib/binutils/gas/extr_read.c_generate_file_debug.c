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
 scalar_t__ DEBUG_STABS ; 
 scalar_t__ debug_type ; 
 int /*<<< orphan*/  stabs_generate_asm_file () ; 

__attribute__((used)) static void
generate_file_debug (void)
{
  if (debug_type == DEBUG_STABS)
    stabs_generate_asm_file ();
}