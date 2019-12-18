#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int tracks_num; TYPE_7__** tracks; TYPE_4__* priv; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_MODULE_T ;
struct TYPE_14__ {TYPE_3__* priv; } ;
struct TYPE_12__ {int /*<<< orphan*/ * module; } ;
struct TYPE_11__ {TYPE_2__* module; } ;
struct TYPE_10__ {TYPE_1__* encodings; } ;
struct TYPE_9__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 unsigned int MKV_MAX_ENCODINGS ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_container_free_track (TYPE_5__*,TYPE_7__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_reader_close(VC_CONTAINER_T *p_ctx)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   unsigned int i, j;

   for(i = 0; i < p_ctx->tracks_num; i++)
   {
      for(j = 0; j < MKV_MAX_ENCODINGS; j++)
         free(p_ctx->tracks[i]->priv->module->encodings[j].data);
      vc_container_free_track(p_ctx, p_ctx->tracks[i]);
   }
   free(module);
   return VC_CONTAINER_SUCCESS;
}