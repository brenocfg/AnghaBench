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
 void* BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 void* seen_in_block ; 
 void* seen_in_insn ; 

__attribute__((used)) static void
df_set_seen (void)
{
  seen_in_block = BITMAP_ALLOC (NULL);
  seen_in_insn = BITMAP_ALLOC (NULL);
}