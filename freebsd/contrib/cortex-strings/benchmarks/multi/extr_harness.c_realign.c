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
 int MAX_ALIGNMENT ; 

__attribute__((used)) static char *realign(char *p, int alignment)
{
  uintptr_t pp = (uintptr_t)p;
  pp = (pp + (MAX_ALIGNMENT - 1)) & ~(MAX_ALIGNMENT - 1);
  pp += alignment;

  return (char *)pp;
}