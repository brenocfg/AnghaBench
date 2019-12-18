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
typedef  int int64_t ;
struct TYPE_6__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
struct TYPE_7__ {int frame_index; int frame_size_samples; int sample_rate; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_5__ {TYPE_3__* module; } ;

/* Variables and functions */
 int INT64_C (int) ; 

__attribute__((used)) static int64_t mpga_calculate_frame_time( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   int64_t time;
   time = INT64_C(1000000) * module->frame_index *
      module->frame_size_samples / module->sample_rate;
   return time;
}