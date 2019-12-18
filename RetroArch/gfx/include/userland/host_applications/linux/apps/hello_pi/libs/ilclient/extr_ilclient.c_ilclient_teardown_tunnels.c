#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sink_port; TYPE_1__* sink; int /*<<< orphan*/  source_port; TYPE_2__* source; } ;
struct TYPE_6__ {int /*<<< orphan*/  comp; } ;
struct TYPE_5__ {int /*<<< orphan*/  comp; } ;
typedef  TYPE_3__ TUNNEL_T ;
typedef  scalar_t__ OMX_ERRORTYPE ;

/* Variables and functions */
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_SetupTunnel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_assert (int) ; 

void ilclient_teardown_tunnels(TUNNEL_T *tunnel)
{
   int i;
   OMX_ERRORTYPE error;

   i=0;;
   while (tunnel[i].source)
   {
      error = OMX_SetupTunnel(tunnel[i].source->comp, tunnel[i].source_port, NULL, 0);
      vc_assert(error == OMX_ErrorNone);

      error = OMX_SetupTunnel(tunnel[i].sink->comp, tunnel[i].sink_port, NULL, 0);
      vc_assert(error == OMX_ErrorNone);
      i++;
   }
}