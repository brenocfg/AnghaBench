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

__attribute__((used)) static float applyCalibration(float inval,float minval, float maxval,float centerval)
{
   float ret;
   /* We don't use the exact ranges but the ranges +1 in case we get bad calibration
    * data - avoid div0 */

   if (inval == centerval)
      ret = 0;
   else if (inval < centerval)
      ret = (inval - centerval) / (centerval - minval + 1);
   else
      ret = (inval - centerval) / (maxval - centerval + 1);
   return ret;
}