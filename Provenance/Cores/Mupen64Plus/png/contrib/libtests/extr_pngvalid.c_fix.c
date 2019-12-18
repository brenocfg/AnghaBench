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
typedef  int /*<<< orphan*/  png_fixed_point ;

/* Variables and functions */
 double PNG_FP_1 ; 
 double floor (double) ; 

__attribute__((used)) static png_fixed_point
fix(double d)
{
   d = floor(d * PNG_FP_1 + .5);
   return (png_fixed_point)d;
}