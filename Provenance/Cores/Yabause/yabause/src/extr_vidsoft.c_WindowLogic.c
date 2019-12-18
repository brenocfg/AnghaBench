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

int WindowLogic(int wctl, int w0, int w1)
{
   if (((wctl & 0x80) == 0x80))
      /* AND logic, returns 0 only if both the windows are active */
      return w0 || w1;
   else
      /* OR logic, returns 0 if one of the windows is active */
      return w0 && w1;
}