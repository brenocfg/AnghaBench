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
 scalar_t__ cache_pc_function_high ; 
 scalar_t__ cache_pc_function_low ; 
 char* cache_pc_function_name ; 
 int /*<<< orphan*/ * cache_pc_function_section ; 

void
clear_pc_function_cache (void)
{
  cache_pc_function_low = 0;
  cache_pc_function_high = 0;
  cache_pc_function_name = (char *) 0;
  cache_pc_function_section = NULL;
}