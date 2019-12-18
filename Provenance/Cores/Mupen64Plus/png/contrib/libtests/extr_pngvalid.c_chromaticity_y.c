#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double Y; double X; double Z; } ;
typedef  TYPE_1__ CIE_color ;

/* Variables and functions */

__attribute__((used)) static double
chromaticity_y(CIE_color c)
{
   return c.Y / (c.X + c.Y + c.Z);
}