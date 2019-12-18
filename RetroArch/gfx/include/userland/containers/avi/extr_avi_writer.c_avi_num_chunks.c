#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {unsigned int tracks_num; TYPE_3__** tracks; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {TYPE_1__* module; } ;
struct TYPE_6__ {scalar_t__ chunk_index; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t avi_num_chunks( VC_CONTAINER_T *p_ctx )
{
   unsigned int i;
   uint32_t num_chunks = 0;
   for (i = 0; i < p_ctx->tracks_num; i++)
      num_chunks += p_ctx->tracks[i]->priv->module->chunk_index;

   return num_chunks;
}