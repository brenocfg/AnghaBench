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
 scalar_t__ ATR_END ; 
 char const** attribute_names ; 

const char *
ada_attribute_name (int n)
{
  if (n > 0 && n < (int) ATR_END)
    return attribute_names[n];
  else
    return attribute_names[0];
}