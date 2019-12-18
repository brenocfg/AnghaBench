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
typedef  int /*<<< orphan*/  qnx_input_t ;
struct TYPE_3__ {int port; int device; int index; int /*<<< orphan*/  id; scalar_t__* analog1; scalar_t__* analog0; scalar_t__ buttons; scalar_t__ buttonCount; scalar_t__ analogCount; scalar_t__ type; scalar_t__ handle; } ;
typedef  TYPE_1__ qnx_input_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qnx_init_controller(qnx_input_t *qnx, qnx_input_device_t* controller)
{
   if (!qnx)
      return;

   /* Initialize controller values. */
#ifdef HAVE_BB10
   controller->handle      = 0;
#endif
   controller->type        = 0;
   controller->analogCount = 0;
   controller->buttonCount = 0;
   controller->buttons     = 0;
   controller->analog0[0]  = 0;
   controller->analog0[1]  = 0;
   controller->analog0[2]  = 0;
   controller->analog1[0]  = 0;
   controller->analog1[1]  = 0;
   controller->analog1[2]  = 0;
   controller->port        = -1;
   controller->device      = -1;
   controller->index       = -1;

   memset(controller->id, 0, sizeof(controller->id));
}