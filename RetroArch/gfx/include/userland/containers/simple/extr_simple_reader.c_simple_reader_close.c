#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_T ;
struct TYPE_13__ {int tracks_num; TYPE_4__** tracks; TYPE_3__* priv; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_MODULE_T ;
struct TYPE_11__ {int /*<<< orphan*/ * module; } ;
struct TYPE_10__ {TYPE_1__* module; } ;
struct TYPE_9__ {scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_container_free_track (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  vc_container_io_close (scalar_t__) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T simple_reader_close( VC_CONTAINER_T *ctx )
{
   VC_CONTAINER_MODULE_T *module = ctx->priv->module;

   for (; ctx->tracks_num > 0; ctx->tracks_num--)
   {
      VC_CONTAINER_TRACK_T *track = ctx->tracks[ctx->tracks_num-1];
      if (track->priv->module->io)
         vc_container_io_close(track->priv->module->io);
      vc_container_free_track(ctx, track);
   }

   free(module);
   return VC_CONTAINER_SUCCESS;
}