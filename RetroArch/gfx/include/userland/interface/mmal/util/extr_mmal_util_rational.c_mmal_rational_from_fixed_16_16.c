#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ MMAL_RATIONAL_T ;

/* Variables and functions */
 int /*<<< orphan*/  Q16_ONE ; 
 int /*<<< orphan*/  mmal_rational_simplify (TYPE_1__*) ; 

MMAL_RATIONAL_T mmal_rational_from_fixed_16_16(int32_t fixed)
{
   MMAL_RATIONAL_T result = { fixed, Q16_ONE };
   mmal_rational_simplify(&result);
   return result;
}