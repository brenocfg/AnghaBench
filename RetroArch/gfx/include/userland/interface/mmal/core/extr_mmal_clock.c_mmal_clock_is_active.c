#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  is_active; } ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_T ;
typedef  TYPE_1__ MMAL_CLOCK_PRIVATE_T ;
typedef  int /*<<< orphan*/  MMAL_BOOL_T ;

/* Variables and functions */

MMAL_BOOL_T mmal_clock_is_active(MMAL_CLOCK_T *clock)
{
   return ((MMAL_CLOCK_PRIVATE_T*)clock)->is_active;
}