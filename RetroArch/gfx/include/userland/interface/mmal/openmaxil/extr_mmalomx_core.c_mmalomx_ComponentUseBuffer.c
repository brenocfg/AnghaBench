#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ state; size_t ports_num; TYPE_4__* ports; } ;
struct TYPE_18__ {int actions; int populated; scalar_t__ buffers; scalar_t__ direction; TYPE_2__* mmal; void* buffers_allocated; } ;
struct TYPE_15__ {int /*<<< orphan*/  nVersion; } ;
struct TYPE_17__ {int nSize; size_t nAllocLen; size_t nInputPortIndex; size_t nOutputPortIndex; void* pInputPortPrivate; void* pOutputPortPrivate; void* pAppPrivate; int /*<<< orphan*/ * pBuffer; TYPE_1__ nVersion; } ;
struct TYPE_16__ {size_t buffer_size_min; size_t buffer_size; scalar_t__ buffer_num; } ;
typedef  int /*<<< orphan*/  OMX_U8 ;
typedef  size_t OMX_U32 ;
typedef  void* OMX_PTR ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  TYPE_3__ OMX_BUFFERHEADERTYPE ;
typedef  int MMAL_BOOL_T ;
typedef  TYPE_4__ MMALOMX_PORT_T ;
typedef  TYPE_5__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LOG_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,TYPE_3__**,int,void*,int,int /*<<< orphan*/ *) ; 
 int MMALOMX_ACTION_CHECK_ALLOCATED ; 
 int /*<<< orphan*/  MMALOMX_LOCK_PORT (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  MMALOMX_UNLOCK_PORT (TYPE_5__*,TYPE_4__*) ; 
 void* MMAL_FALSE ; 
 scalar_t__ OMX_DirInput ; 
 scalar_t__ OMX_ErrorBadParameter ; 
 scalar_t__ OMX_ErrorBadPortIndex ; 
 scalar_t__ OMX_ErrorIncorrectStateOperation ; 
 scalar_t__ OMX_ErrorInsufficientResources ; 
 scalar_t__ OMX_ErrorInvalidComponent ; 
 scalar_t__ OMX_ErrorInvalidState ; 
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_StateInvalid ; 
 int /*<<< orphan*/  OMX_VERSION ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  mmalomx_commands_actions_check (TYPE_5__*) ; 
 int /*<<< orphan*/  mmalomx_commands_actions_signal (TYPE_5__*) ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_ComponentUseBuffer(
   OMX_HANDLETYPE hComponent,
   OMX_BUFFERHEADERTYPE** ppBuffer,
   OMX_U32 nPortIndex,
   OMX_PTR pAppPrivate,
   OMX_U32 nSizeBytes,
   OMX_U8* pBuffer)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;
   OMX_ERRORTYPE status = OMX_ErrorNone;
   MMAL_BOOL_T populated = MMAL_FALSE;
   OMX_BUFFERHEADERTYPE *buffer;
   MMALOMX_PORT_T *port;

   LOG_TRACE("hComponent %p, ppBufferHdr %p, nPortIndex %i, pAppPrivate %p,"
             " nSizeBytes %i, pBuffer %p", hComponent, ppBuffer,
             (int)nPortIndex, pAppPrivate, (int)nSizeBytes, pBuffer);

   /* Sanity checks */
   if (!hComponent)
      return OMX_ErrorInvalidComponent;
   if (!ppBuffer)
      return OMX_ErrorBadParameter;
   if (component->state == OMX_StateInvalid)
      return OMX_ErrorInvalidState;
   if (nPortIndex >= component->ports_num)
      return OMX_ErrorBadPortIndex;

   /* Make sure any previous command has been processed.
   * This is not ideal since done inline but in practice the actual
   * notification to the client will not be done as part of this call. */
   mmalomx_commands_actions_check(component);

   port = &component->ports[nPortIndex];
   MMALOMX_LOCK_PORT(component, port);

   if (!(port->actions & MMALOMX_ACTION_CHECK_ALLOCATED))
      status = OMX_ErrorIncorrectStateOperation;
   if (port->populated)
      status = OMX_ErrorIncorrectStateOperation;
   if (status != OMX_ErrorNone)
      goto error;

   /* Check for mismatched calls to UseBuffer/AllocateBuffer */
   if (port->buffers && port->buffers_allocated)
   {
      status = OMX_ErrorBadParameter;
      goto error;
   }

   /* Sanity check buffer size */
   if (nSizeBytes < port->mmal->buffer_size_min)
   {
      LOG_ERROR("buffer size too small (%i/%i)", (int)nSizeBytes,
                (int)port->mmal->buffer_size_min);
      status = OMX_ErrorBadParameter;
      goto error;
   }
   if (!port->buffers)
      port->mmal->buffer_size = nSizeBytes;
   if (nSizeBytes > port->mmal->buffer_size)
   {
      LOG_ERROR("buffer size too big (%i/%i)", (int)nSizeBytes,
                (int)port->mmal->buffer_size);
      status = OMX_ErrorBadParameter;
      goto error;
   }

   buffer = calloc( 1, sizeof(*buffer) );
   if (!buffer)
   {
      status = OMX_ErrorInsufficientResources;
      goto error;
   }

   buffer->nSize = sizeof(*buffer);
   buffer->nVersion.nVersion = OMX_VERSION;
   buffer->nAllocLen = nSizeBytes;
   buffer->pBuffer = pBuffer;
   buffer->pAppPrivate = pAppPrivate;
   if (port->direction == OMX_DirInput)
   {
      buffer->nInputPortIndex = nPortIndex;
      buffer->pOutputPortPrivate = pAppPrivate;
   }
   else
   {
      buffer->nOutputPortIndex = nPortIndex;
      buffer->pInputPortPrivate = pAppPrivate;
   }

   *ppBuffer = buffer;
   port->buffers++;
   port->buffers_allocated = MMAL_FALSE;
   port->populated = populated = port->buffers == port->mmal->buffer_num;

   MMALOMX_UNLOCK_PORT(component, port);

   LOG_DEBUG("allocated %i/%i buffers", port->buffers, port->mmal->buffer_num);

   if (populated)
      mmalomx_commands_actions_signal(component);

   return OMX_ErrorNone;

error:
   MMALOMX_UNLOCK_PORT(component, port);
   return status;
}