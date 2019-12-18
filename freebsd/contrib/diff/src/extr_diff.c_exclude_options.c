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
 int EXCLUDE_WILDCARDS ; 
 int FNM_CASEFOLD ; 
 scalar_t__ ignore_file_name_case ; 

__attribute__((used)) static int
exclude_options (void)
{
  return EXCLUDE_WILDCARDS | (ignore_file_name_case ? FNM_CASEFOLD : 0);
}