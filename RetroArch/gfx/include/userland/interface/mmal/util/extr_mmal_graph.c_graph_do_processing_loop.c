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
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {scalar_t__ module; } ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;

/* Variables and functions */
 scalar_t__ graph_do_processing (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void graph_do_processing_loop(MMAL_COMPONENT_T *component)
{
   while (graph_do_processing((MMAL_GRAPH_PRIVATE_T *)component->priv->module));
}