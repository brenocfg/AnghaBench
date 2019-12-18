#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * output; } ;
struct TYPE_4__ {TYPE_2__* encoder_component; scalar_t__ encoder_pool; } ;
typedef  TYPE_1__ RASPIVID_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_component_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_port_pool_destroy (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void destroy_encoder_component(RASPIVID_STATE *state)
{
   // Get rid of any port buffers first
   if (state->encoder_pool)
   {
      mmal_port_pool_destroy(state->encoder_component->output[0], state->encoder_pool);
   }

   if (state->encoder_component)
   {
      mmal_component_destroy(state->encoder_component);
      state->encoder_component = NULL;
   }
}