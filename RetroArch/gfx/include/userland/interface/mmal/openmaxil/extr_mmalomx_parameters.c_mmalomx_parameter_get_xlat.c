#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mmal_generic ;
struct TYPE_31__ {size_t ports_num; TYPE_2__* ports; TYPE_1__* mmal; } ;
struct TYPE_27__ {int size; int /*<<< orphan*/  id; } ;
struct TYPE_30__ {TYPE_4__ header; } ;
struct TYPE_29__ {int nSize; size_t nPortIndex; } ;
struct TYPE_26__ {scalar_t__ (* custom ) (int /*<<< orphan*/ ,TYPE_5__ const*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ;scalar_t__ (* list ) (int /*<<< orphan*/ ,TYPE_5__ const*,int,TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ;scalar_t__ (* generic ) (int /*<<< orphan*/ ,TYPE_5__ const*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ;scalar_t__ (* simple ) (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ;} ;
struct TYPE_28__ {int omx_size; scalar_t__ type; int mmal_size; int xlat_enum_num; TYPE_3__ fn; scalar_t__ double_translation; int /*<<< orphan*/  mmal_id; scalar_t__ portless; } ;
struct TYPE_25__ {int /*<<< orphan*/ * mmal; } ;
struct TYPE_24__ {int /*<<< orphan*/ * control; } ;
typedef  int OMX_U32 ;
typedef  scalar_t__ OMX_PTR ;
typedef  int /*<<< orphan*/  OMX_INDEXTYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_5__ MMALOMX_PARAM_TRANSLATION_T ;
typedef  TYPE_6__ MMALOMX_PARAM_OMX_HEADER_T ;
typedef  TYPE_7__ MMALOMX_PARAM_MMAL_GENERIC_T ;
typedef  TYPE_8__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMALOMX_PARAM_MAPPING_TO_OMX ; 
 scalar_t__ MMALOMX_PARAM_TRANSLATION_TYPE_DIRECT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  OMX_ErrorBadParameter ; 
 int /*<<< orphan*/  OMX_ErrorBadPortIndex ; 
 int /*<<< orphan*/  OMX_ErrorInsufficientResources ; 
 int /*<<< orphan*/  OMX_ErrorNoMore ; 
 int /*<<< orphan*/  OMX_ErrorNotImplemented ; 
 TYPE_4__* mmal_port_parameter_alloc_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ mmal_port_parameter_get (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  mmalil_error_to_omx (scalar_t__) ; 
 TYPE_5__* mmalomx_find_parameter_from_omx_id (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_5__ const*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_5__ const*,int,TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,TYPE_5__ const*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,TYPE_5__ const*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub6 (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  vcos_free (TYPE_4__*) ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_parameter_get_xlat(MMALOMX_COMPONENT_T *component,
   OMX_INDEXTYPE nParamIndex, OMX_PTR pParam)
{
   const MMALOMX_PARAM_TRANSLATION_T *xlat = mmalomx_find_parameter_from_omx_id(nParamIndex);
   MMALOMX_PARAM_OMX_HEADER_T *omx_header = (MMALOMX_PARAM_OMX_HEADER_T *)pParam;
   MMALOMX_PARAM_MMAL_GENERIC_T mmal_generic;
   MMAL_PARAMETER_HEADER_T *mmal_header = &mmal_generic.header;
   MMAL_PORT_T *mmal_port = component->mmal->control;
   MMAL_STATUS_T status = MMAL_SUCCESS;

   if (!xlat)
      return OMX_ErrorNotImplemented;

   if (!xlat->portless)
   {
      if (omx_header->nSize < sizeof(*omx_header))
         return OMX_ErrorBadParameter;
      if (omx_header->nPortIndex >= component->ports_num)
         return OMX_ErrorBadPortIndex;
      mmal_port = component->ports[omx_header->nPortIndex].mmal;
   }

   if (omx_header->nSize < xlat->omx_size)
      return OMX_ErrorBadParameter;

   /* Handle the direct case first */
   if (xlat->type == MMALOMX_PARAM_TRANSLATION_TYPE_DIRECT)
   {
      OMX_U32 size;
      mmal_header = (MMAL_PARAMETER_HEADER_T *)(((uint8_t *)pParam) + (xlat->portless ? 0 : 4));
      mmal_generic.header = *mmal_header;
      mmal_header->size = omx_header->nSize - (xlat->portless ? 0 : 4);
      mmal_header->id = xlat->mmal_id;
      status = mmal_port_parameter_get(mmal_port, mmal_header);
      *mmal_header = mmal_generic.header;
      size = mmal_header->size + (xlat->portless ? 0 : 4);
      omx_header->nSize = size;
      return mmalil_error_to_omx(status);
   }

   if (xlat->fn.custom)
   {
      return mmalil_error_to_omx(xlat->fn.custom(MMALOMX_PARAM_MAPPING_TO_OMX, xlat, mmal_header,
         pParam, mmal_port));
   }

   if (xlat->fn.list)
   {
      OMX_U32 index, elements;
      mmal_header = mmal_port_parameter_alloc_get(mmal_port, xlat->mmal_id,
         10*xlat->mmal_size, &status);
      if (!mmal_header)
         return OMX_ErrorInsufficientResources;

      /* Check we're not requesting too much */
      index = *(OMX_U32 *)(((uint8_t *)pParam) + xlat->xlat_enum_num);
      elements = (mmal_header->size - sizeof(MMAL_PARAMETER_HEADER_T)) /
         (xlat->mmal_size - sizeof(MMAL_PARAMETER_HEADER_T));
      if (index >= elements)
      {
         vcos_free(mmal_header);
         return OMX_ErrorNoMore;
      }
      status = xlat->fn.list(MMALOMX_PARAM_MAPPING_TO_OMX, xlat, index, mmal_header, pParam, mmal_port);
      vcos_free(mmal_header);
      return mmalil_error_to_omx(status);
   }

   if (!xlat->fn.generic && !xlat->fn.simple)
   {
      // FIXME
      return OMX_ErrorNotImplemented;
   }

   // FIXME: check size of mmal_generic is sufficient
   if (sizeof(mmal_generic) < xlat->mmal_size)
      return OMX_ErrorBadParameter;

   mmal_header->size = xlat->mmal_size;
   mmal_header->id = xlat->mmal_id;

   if (xlat->double_translation)
   {
      if (xlat->fn.generic)
         status = xlat->fn.generic(MMALOMX_PARAM_MAPPING_TO_MMAL, xlat, mmal_header, pParam, mmal_port);
      else
         status = xlat->fn.simple(MMALOMX_PARAM_MAPPING_TO_MMAL, mmal_header, pParam);
   }
   if (status != MMAL_SUCCESS)
      goto error;

   status = mmal_port_parameter_get(mmal_port, mmal_header);
   if (status != MMAL_SUCCESS)
      goto error;

   if (xlat->fn.generic)
      status = xlat->fn.generic(MMALOMX_PARAM_MAPPING_TO_OMX, xlat, mmal_header, pParam, mmal_port);
   else
      status = xlat->fn.simple(MMALOMX_PARAM_MAPPING_TO_OMX, mmal_header, pParam);

 error:
   return mmalil_error_to_omx(status);
}