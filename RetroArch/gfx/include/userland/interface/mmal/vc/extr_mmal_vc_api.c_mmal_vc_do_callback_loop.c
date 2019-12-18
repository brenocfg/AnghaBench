#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {TYPE_1__* module; } ;
struct TYPE_6__ {int /*<<< orphan*/  callback_queue; } ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;

/* Variables and functions */
 scalar_t__ mmal_queue_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_vc_do_callback (TYPE_3__*) ; 

__attribute__((used)) static void mmal_vc_do_callback_loop(MMAL_COMPONENT_T *component)
{
   while (mmal_queue_length(component->priv->module->callback_queue))
      mmal_vc_do_callback(component);
}