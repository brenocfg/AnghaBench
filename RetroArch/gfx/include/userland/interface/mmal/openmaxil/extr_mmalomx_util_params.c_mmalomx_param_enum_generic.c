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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {unsigned int xlat_enum_num; TYPE_1__* xlat_enum; scalar_t__ portless; } ;
struct TYPE_4__ {scalar_t__ omx; scalar_t__ mmal; } ;
typedef  scalar_t__ OMX_PTR ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_2__ MMALOMX_PARAM_TRANSLATION_T ;
typedef  int /*<<< orphan*/  MMALOMX_PARAM_OMX_HEADER_T ;
typedef  scalar_t__ MMALOMX_PARAM_MAPPING_DIRECTION ;

/* Variables and functions */
 scalar_t__ MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  VCOS_ALERT (char*,unsigned int) ; 

MMAL_STATUS_T mmalomx_param_enum_generic(MMALOMX_PARAM_MAPPING_DIRECTION dir,
   const MMALOMX_PARAM_TRANSLATION_T *xlat,
   MMAL_PARAMETER_HEADER_T *mmal_param, OMX_PTR omx_param, MMAL_PORT_T *mmal_port)
{
   uint32_t *mmal = (uint32_t *)(((uint8_t *)mmal_param) + sizeof(MMAL_PARAMETER_HEADER_T));
   uint32_t *omx = (uint32_t *)(((uint8_t *)omx_param) + sizeof(MMALOMX_PARAM_OMX_HEADER_T));
   unsigned int i = 0;
   MMAL_PARAM_UNUSED(mmal_port);

   if (xlat->portless)
      omx -= 1;

   /* Find translation entry in lookup table */
   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
      for (i = 0; i < xlat->xlat_enum_num && xlat->xlat_enum->omx != *omx; i++);
   else
      for (i = 0; i < xlat->xlat_enum_num && xlat->xlat_enum->mmal != *mmal; i++);

   if (i == xlat->xlat_enum_num)
   {
      if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
         VCOS_ALERT("mmalomx_param_enum_generic: omx enum value %u not supported", (unsigned int)*omx);
      else
         VCOS_ALERT("mmalomx_param_enum_generic: mmal enum value %u not supported", (unsigned int)*mmal);
      return MMAL_EINVAL;
   }

   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
      *mmal = xlat->xlat_enum[i].mmal;
   else
      *omx = xlat->xlat_enum[i].omx;

   return MMAL_SUCCESS;
}