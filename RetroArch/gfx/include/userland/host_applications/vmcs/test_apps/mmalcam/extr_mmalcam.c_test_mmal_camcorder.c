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
typedef  int /*<<< orphan*/  MMALCAM_BEHAVIOUR_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int) ; 
 int /*<<< orphan*/  stop ; 
 int test_mmal_start_camcorder (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *test_mmal_camcorder(void *id)
{
   MMALCAM_BEHAVIOUR_T *behaviour = (MMALCAM_BEHAVIOUR_T *)id;
   int value;

   value = test_mmal_start_camcorder(&stop, behaviour);

   LOG_TRACE("Thread terminating, result %d", value);
   return (void *)value;
}