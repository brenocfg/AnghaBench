#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int dir; scalar_t__ reset; int /*<<< orphan*/  stats; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; } ;
struct TYPE_10__ {int /*<<< orphan*/  stats_lock; TYPE_1__ stats; } ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {TYPE_4__* core; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_PORT_PRIVATE_CORE_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_5__ MMAL_PARAMETER_CORE_STATISTICS_T ;
typedef  int /*<<< orphan*/  MMAL_CORE_STATISTICS_T ;

/* Variables and functions */
#define  MMAL_CORE_STATS_RX 128 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_get_core_stats(MMAL_PORT_T *port, MMAL_PARAMETER_HEADER_T *param)
{
   MMAL_PARAMETER_CORE_STATISTICS_T *stats_param = (MMAL_PARAMETER_CORE_STATISTICS_T*)param;
   MMAL_CORE_STATISTICS_T *stats = &stats_param->stats;
   MMAL_CORE_STATISTICS_T *src_stats;
   MMAL_PORT_PRIVATE_CORE_T *core = port->priv->core;
   vcos_mutex_lock(&core->stats_lock);
   switch (stats_param->dir)
   {
   case MMAL_CORE_STATS_RX:
      src_stats = &port->priv->core->stats.rx;
      break;
   default:
      src_stats = &port->priv->core->stats.tx;
      break;
   }
   *stats = *src_stats;
   if (stats_param->reset)
      memset(src_stats, 0, sizeof(*src_stats));
   vcos_mutex_unlock(&core->stats_lock);
   return MMAL_SUCCESS;
}