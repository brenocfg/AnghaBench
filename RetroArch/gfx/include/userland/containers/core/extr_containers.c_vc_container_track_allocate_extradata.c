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
struct TYPE_7__ {TYPE_2__* priv; TYPE_1__* format; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_6__ {unsigned int extradata_size; scalar_t__ extradata; } ;
struct TYPE_5__ {scalar_t__ extradata; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ malloc (unsigned int) ; 

VC_CONTAINER_STATUS_T vc_container_track_allocate_extradata( VC_CONTAINER_T *context,
   VC_CONTAINER_TRACK_T *p_track, unsigned int extra_size )
{
   VC_CONTAINER_PARAM_UNUSED(context);

   /* Sanity check the size of the extra data */
   if(extra_size > 100*1024) return VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION;

   /* Check if we need to allocate a buffer */
   if(extra_size > p_track->priv->extradata_size)
   {
      p_track->priv->extradata_size = 0;
      if(p_track->priv->extradata) free(p_track->priv->extradata);
      p_track->priv->extradata = malloc(extra_size);
      p_track->format->extradata = p_track->priv->extradata;
      if(!p_track->priv->extradata) return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
      p_track->priv->extradata_size = extra_size;
   }
   p_track->format->extradata = p_track->priv->extradata;

   return VC_CONTAINER_SUCCESS;
}