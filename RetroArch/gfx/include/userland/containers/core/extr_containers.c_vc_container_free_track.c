#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
struct TYPE_5__ {TYPE_2__* drmdata; TYPE_2__* extradata; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void vc_container_free_track( VC_CONTAINER_T *context, VC_CONTAINER_TRACK_T *p_track )
{
   VC_CONTAINER_PARAM_UNUSED(context);
   if(p_track)
   {
      if(p_track->priv->extradata) free(p_track->priv->extradata);
      if(p_track->priv->drmdata) free(p_track->priv->drmdata);
      free(p_track);
   }
}