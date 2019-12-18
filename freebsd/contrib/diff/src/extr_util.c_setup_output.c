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
 char const* current_name0 ; 
 char const* current_name1 ; 
 int currently_recursive ; 
 scalar_t__ outfile ; 

void
setup_output (char const *name0, char const *name1, bool recursive)
{
  current_name0 = name0;
  current_name1 = name1;
  currently_recursive = recursive;
  outfile = 0;
}