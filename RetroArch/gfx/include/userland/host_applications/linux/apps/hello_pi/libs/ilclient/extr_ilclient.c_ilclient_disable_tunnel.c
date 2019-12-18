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
struct TYPE_5__ {int /*<<< orphan*/  error_mask; int /*<<< orphan*/  comp; } ;
struct TYPE_4__ {TYPE_2__* sink; TYPE_2__* source; int /*<<< orphan*/  sink_port; int /*<<< orphan*/  source_port; } ;
typedef  TYPE_1__ TUNNEL_T ;
typedef  scalar_t__ OMX_ERRORTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ILCLIENT_ERROR_UNPOPULATED ; 
 int /*<<< orphan*/  OMX_CommandPortDisable ; 
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ilclient_wait_for_command_complete (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_assert (int) ; 

void ilclient_disable_tunnel(TUNNEL_T *tunnel)
{
   OMX_ERRORTYPE error;

   if(tunnel->source == 0 || tunnel->sink == 0)
      return;

   tunnel->source->error_mask |= ILCLIENT_ERROR_UNPOPULATED;
   tunnel->sink->error_mask |= ILCLIENT_ERROR_UNPOPULATED;

   error = OMX_SendCommand(tunnel->source->comp, OMX_CommandPortDisable, tunnel->source_port, NULL);
   vc_assert(error == OMX_ErrorNone);

   error = OMX_SendCommand(tunnel->sink->comp, OMX_CommandPortDisable, tunnel->sink_port, NULL);
   vc_assert(error == OMX_ErrorNone);

   if(ilclient_wait_for_command_complete(tunnel->source, OMX_CommandPortDisable, tunnel->source_port) < 0)
      vc_assert(0);

   if(ilclient_wait_for_command_complete(tunnel->sink, OMX_CommandPortDisable, tunnel->sink_port) < 0)
      vc_assert(0);

   tunnel->source->error_mask &= ~ILCLIENT_ERROR_UNPOPULATED;
   tunnel->sink->error_mask &= ~ILCLIENT_ERROR_UNPOPULATED;
}