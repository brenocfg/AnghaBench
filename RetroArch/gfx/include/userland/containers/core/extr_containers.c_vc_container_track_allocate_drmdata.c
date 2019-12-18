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
typedef  TYPE_2__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_4__ {unsigned int drmdata_size; scalar_t__ drmdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ malloc (unsigned int) ; 

VC_CONTAINER_STATUS_T vc_container_track_allocate_drmdata( VC_CONTAINER_T *context,
   VC_CONTAINER_TRACK_T *p_track, unsigned int size )
{
   VC_CONTAINER_PARAM_UNUSED(context);

   /* Sanity check the size of the drm data */
   if(size > 200*1024) return VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION;

   /* Check if we need to allocate a buffer */
   if(size > p_track->priv->drmdata_size)
   {
      p_track->priv->drmdata_size = 0;
      if(p_track->priv->drmdata) free(p_track->priv->drmdata);
      p_track->priv->drmdata = malloc(size);
      if(!p_track->priv->drmdata) return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
      p_track->priv->drmdata_size = size;
   }

   return VC_CONTAINER_SUCCESS;
}