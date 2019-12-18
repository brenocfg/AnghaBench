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
 scalar_t__ SUPPORTS_ONE_ONLY ; 
 int SUPPORTS_WEAK ; 

int
supports_one_only (void)
{
  if (SUPPORTS_ONE_ONLY)
    return 1;
  return SUPPORTS_WEAK;
}