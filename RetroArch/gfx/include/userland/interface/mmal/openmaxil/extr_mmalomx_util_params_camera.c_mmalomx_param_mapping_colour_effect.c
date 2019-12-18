#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  v; int /*<<< orphan*/  u; int /*<<< orphan*/  enable; } ;
struct TYPE_3__ {int /*<<< orphan*/  nCustomizedV; int /*<<< orphan*/  nCustomizedU; int /*<<< orphan*/  bColorEnhancement; } ;
typedef  scalar_t__ OMX_PTR ;
typedef  TYPE_1__ OMX_CONFIG_COLORENHANCEMENTTYPE ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_2__ MMAL_PARAMETER_COLOURFX_T ;
typedef  scalar_t__ MMALOMX_PARAM_MAPPING_DIRECTION ;

/* Variables and functions */
 scalar_t__ MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 

__attribute__((used)) static MMAL_STATUS_T mmalomx_param_mapping_colour_effect(MMALOMX_PARAM_MAPPING_DIRECTION dir,
   MMAL_PARAMETER_HEADER_T *mmal_param, OMX_PTR omx_param)
{
   OMX_CONFIG_COLORENHANCEMENTTYPE *omx = (OMX_CONFIG_COLORENHANCEMENTTYPE *)omx_param;
   MMAL_PARAMETER_COLOURFX_T *mmal = (MMAL_PARAMETER_COLOURFX_T *)mmal_param;

   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
   {
      mmal->enable = omx->bColorEnhancement;
      mmal->u = omx->nCustomizedU;
      mmal->v = omx->nCustomizedV;
   }
   else
   {
      omx->bColorEnhancement = mmal->enable;
      omx->nCustomizedU = mmal->u;
      omx->nCustomizedV = mmal->v;
   }

   return MMAL_SUCCESS;
}