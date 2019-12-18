#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  sema; TYPE_3__* out_list; TYPE_3__* in_list; int /*<<< orphan*/  comp; int /*<<< orphan*/  bufname; } ;
struct TYPE_14__ {int /*<<< orphan*/  pAppPrivate; } ;
struct TYPE_12__ {int /*<<< orphan*/  nVersion; } ;
struct TYPE_13__ {int nSize; int nPortIndex; scalar_t__ bEnabled; int nBufferCountActual; scalar_t__ nBufferSize; scalar_t__ eDir; int /*<<< orphan*/  nBufferAlignment; TYPE_1__ nVersion; } ;
typedef  scalar_t__ OMX_STATETYPE ;
typedef  TYPE_2__ OMX_PARAM_PORTDEFINITIONTYPE ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  TYPE_3__ OMX_BUFFERHEADERTYPE ;
typedef  unsigned char* (* ILCLIENT_MALLOC_T ) (void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  (* ILCLIENT_FREE_T ) (void*,unsigned char*) ;
typedef  TYPE_4__ COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  OMX_CommandPortEnable ; 
 scalar_t__ OMX_DirInput ; 
 scalar_t__ OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_EventError ; 
 scalar_t__ OMX_FALSE ; 
 scalar_t__ OMX_GetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ OMX_GetState (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  OMX_IndexParamPortDefinition ; 
 scalar_t__ OMX_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ OMX_StateExecuting ; 
 scalar_t__ OMX_StateIdle ; 
 scalar_t__ OMX_StatePause ; 
 scalar_t__ OMX_UseBuffer (int /*<<< orphan*/ ,TYPE_3__**,int,int /*<<< orphan*/ *,scalar_t__,unsigned char*) ; 
 int /*<<< orphan*/  OMX_VERSION ; 
 int /*<<< orphan*/  ilclient_disable_port_buffers (TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (void*,unsigned char*),void*) ; 
 int /*<<< orphan*/  ilclient_remove_event (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ilclient_wait_for_command_complete (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vc_assert (int) ; 
 int /*<<< orphan*/  vcos_free (unsigned char*) ; 
 unsigned char* vcos_malloc_aligned (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 

int ilclient_enable_port_buffers(COMPONENT_T *comp, int portIndex,
                                 ILCLIENT_MALLOC_T ilclient_malloc,
                                 ILCLIENT_FREE_T ilclient_free,
                                 void *private)
{
   OMX_ERRORTYPE error;
   OMX_PARAM_PORTDEFINITIONTYPE portdef;
   OMX_BUFFERHEADERTYPE *list = NULL, **end = &list;
   OMX_STATETYPE state;
   int i;

   memset(&portdef, 0, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
   portdef.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
   portdef.nVersion.nVersion = OMX_VERSION;
   portdef.nPortIndex = portIndex;

   // work out buffer requirements, check port is in the right state
   error = OMX_GetParameter(comp->comp, OMX_IndexParamPortDefinition, &portdef);
   if(error != OMX_ErrorNone || portdef.bEnabled != OMX_FALSE || portdef.nBufferCountActual == 0 || portdef.nBufferSize == 0)
      return -1;

   // check component is in the right state to accept buffers
   error = OMX_GetState(comp->comp, &state);
   if (error != OMX_ErrorNone || !(state == OMX_StateIdle || state == OMX_StateExecuting || state == OMX_StatePause))
      return -1;

   // send the command
   error = OMX_SendCommand(comp->comp, OMX_CommandPortEnable, portIndex, NULL);
   vc_assert(error == OMX_ErrorNone);

   for (i=0; i != portdef.nBufferCountActual; i++)
   {
      unsigned char *buf;
      if(ilclient_malloc)
         buf = ilclient_malloc(private, portdef.nBufferSize, portdef.nBufferAlignment, comp->bufname);
      else
         buf = vcos_malloc_aligned(portdef.nBufferSize, portdef.nBufferAlignment, comp->bufname);

      if(!buf)
         break;

      error = OMX_UseBuffer(comp->comp, end, portIndex, NULL, portdef.nBufferSize, buf);
      if(error != OMX_ErrorNone)
      {
         if(ilclient_free)
            ilclient_free(private, buf);
         else
            vcos_free(buf);

         break;
      }
      end = (OMX_BUFFERHEADERTYPE **) &((*end)->pAppPrivate);
   }

   // queue these buffers
   vcos_semaphore_wait(&comp->sema);

   if(portdef.eDir == OMX_DirInput)
   {
      *end = comp->in_list;
      comp->in_list = list;
   }
   else
   {
      *end = comp->out_list;
      comp->out_list = list;
   }

   vcos_semaphore_post(&comp->sema);

   if(i != portdef.nBufferCountActual ||
      ilclient_wait_for_command_complete(comp, OMX_CommandPortEnable, portIndex) < 0)
   {
      ilclient_disable_port_buffers(comp, portIndex, NULL, ilclient_free, private);

      // at this point the first command might have terminated with an error, which means that
      // the port is disabled before the disable_port_buffers function is called, so we're left
      // with the error bit set and an error event in the queue.  Clear these now if they exist.
      ilclient_remove_event(comp, OMX_EventError, 0, 1, 1, 0);

      return -1;
   }

   // success
   return 0;
}