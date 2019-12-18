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
 int arm_get_strip_length (char const) ; 

const char *
arm_strip_name_encoding (const char *name)
{
  int skip;

  while ((skip = arm_get_strip_length (* name)))
    name += skip;

  return name;
}