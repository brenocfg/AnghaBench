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
struct TYPE_4__ {int /*<<< orphan*/  scale_rational; } ;
typedef  int /*<<< orphan*/  MMAL_RATIONAL_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_T ;
typedef  TYPE_1__ MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  UNLOCK (TYPE_1__*) ; 

MMAL_RATIONAL_T mmal_clock_scale_get(MMAL_CLOCK_T *clock)
{
   MMAL_CLOCK_PRIVATE_T *private = (MMAL_CLOCK_PRIVATE_T*)clock;
   MMAL_RATIONAL_T scale;

   LOCK(private);
   scale = private->scale_rational;
   UNLOCK(private);

   return scale;
}