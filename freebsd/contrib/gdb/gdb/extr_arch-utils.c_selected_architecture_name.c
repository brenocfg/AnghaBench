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
 char const* set_architecture_string ; 
 scalar_t__ target_architecture_auto ; 

const char *
selected_architecture_name (void)
{
  if (target_architecture_auto)
    return NULL;
  else
    return set_architecture_string;
}