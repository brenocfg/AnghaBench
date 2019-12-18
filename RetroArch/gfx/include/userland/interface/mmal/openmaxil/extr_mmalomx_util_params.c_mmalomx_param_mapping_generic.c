#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int nSize; } ;
struct TYPE_7__ {scalar_t__ portless; } ;
struct TYPE_6__ {int size; scalar_t__ id; } ;
typedef  int /*<<< orphan*/  OMX_U32 ;
typedef  scalar_t__ OMX_PTR ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_1__ MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_2__ MMALOMX_PARAM_TRANSLATION_T ;
typedef  TYPE_3__ MMALOMX_PARAM_OMX_HEADER_T ;
typedef  scalar_t__ MMALOMX_PARAM_MAPPING_DIRECTION ;

/* Variables and functions */
 scalar_t__ MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  VCOS_ALERT (char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

MMAL_STATUS_T mmalomx_param_mapping_generic(MMALOMX_PARAM_MAPPING_DIRECTION dir,
   const MMALOMX_PARAM_TRANSLATION_T *xlat,
   MMAL_PARAMETER_HEADER_T *mmal_param, OMX_PTR omx_param, MMAL_PORT_T *mmal_port)
{
   MMALOMX_PARAM_OMX_HEADER_T *omx_header = (MMALOMX_PARAM_OMX_HEADER_T *)omx_param;
   uint8_t *mmal_data = ((uint8_t *)mmal_param) + sizeof(MMAL_PARAMETER_HEADER_T);
   uint8_t *omx_data = ((uint8_t *)omx_param) + sizeof(MMALOMX_PARAM_OMX_HEADER_T);
   unsigned int size = mmal_param->size - sizeof(MMAL_PARAMETER_HEADER_T);
   MMAL_PARAM_UNUSED(mmal_port);

   if (xlat->portless)
      omx_data -= sizeof(OMX_U32);

   if (((uint8_t *)omx_param) + omx_header->nSize !=
         omx_data + size)
   {
      VCOS_ALERT("mmalomx_param_mapping_generic: mismatch between mmal and omx parameters for (%u)",
                 (unsigned int)mmal_param->id);
      return MMAL_EINVAL;
   }

   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
      memcpy(mmal_data, omx_data, size);
   else
      memcpy(omx_data, mmal_data, size);

   return MMAL_SUCCESS;
}