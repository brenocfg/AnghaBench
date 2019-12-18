#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ MMAL_RATIONAL_T ;

/* Variables and functions */
 TYPE_1__ mmal_rational_add (TYPE_1__,TYPE_1__) ; 

MMAL_RATIONAL_T mmal_rational_subtract(MMAL_RATIONAL_T a, MMAL_RATIONAL_T b)
{
   b.num = -b.num;
   return mmal_rational_add(a, b);
}