#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  component_name ;
struct TYPE_18__ {int flags; int /*<<< orphan*/  sema; int /*<<< orphan*/  event; int /*<<< orphan*/  comp; scalar_t__* bufname; scalar_t__* name; int /*<<< orphan*/ * client; } ;
struct TYPE_17__ {int /*<<< orphan*/  FillBufferDone; int /*<<< orphan*/  EmptyBufferDone; int /*<<< orphan*/  EventHandler; } ;
struct TYPE_15__ {void* nVersion; } ;
struct TYPE_16__ {int nSize; scalar_t__ nPorts; scalar_t__ nStartPortNumber; scalar_t__ eDir; scalar_t__ nBufferCountActual; scalar_t__ nPortIndex; TYPE_1__ nVersion; } ;
typedef  int /*<<< orphan*/  OMX_VERSIONTYPE ;
typedef  scalar_t__ OMX_UUIDTYPE ;
typedef  TYPE_2__ OMX_PORT_PARAM_TYPE ;
typedef  TYPE_2__ OMX_PARAM_PORTDEFINITIONTYPE ;
typedef  int /*<<< orphan*/  OMX_INDEXTYPE ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  TYPE_4__ OMX_CALLBACKTYPE ;
typedef  int /*<<< orphan*/  ILCLIENT_T ;
typedef  int ILCLIENT_CREATE_FLAGS_T ;
typedef  TYPE_5__ COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_PREFIX ; 
 int ILCLIENT_DISABLE_ALL_PORTS ; 
 int ILCLIENT_ENABLE_INPUT_BUFFERS ; 
 int ILCLIENT_ENABLE_OUTPUT_BUFFERS ; 
 int ILCLIENT_OUTPUT_ZERO_BUFFERS ; 
 scalar_t__ OMX_DirOutput ; 
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_GetComponentVersion (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ OMX_GetHandle (int /*<<< orphan*/ *,char*,TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ OMX_GetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  OMX_IndexParamAudioInit ; 
 int /*<<< orphan*/  OMX_IndexParamImageInit ; 
 int /*<<< orphan*/  OMX_IndexParamOtherInit ; 
 int /*<<< orphan*/  OMX_IndexParamPortDefinition ; 
 int /*<<< orphan*/  OMX_IndexParamVideoInit ; 
 int /*<<< orphan*/  OMX_SetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* OMX_VERSION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  ilclient_disable_port (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  ilclient_empty_buffer_done ; 
 int /*<<< orphan*/  ilclient_empty_buffer_done_error ; 
 int /*<<< orphan*/  ilclient_event_handler ; 
 int /*<<< orphan*/  ilclient_fill_buffer_done ; 
 int /*<<< orphan*/  ilclient_fill_buffer_done_error ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_assert (int) ; 
 scalar_t__ vcos_event_flags_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcos_event_flags_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_free (TYPE_5__*) ; 
 TYPE_5__* vcos_malloc (int,char*) ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_snprintf (char*,int,char*,char*,...) ; 

int ilclient_create_component(ILCLIENT_T *client, COMPONENT_T **comp, char *name,
                              ILCLIENT_CREATE_FLAGS_T flags)
{
   OMX_CALLBACKTYPE callbacks;
   OMX_ERRORTYPE error;
   char component_name[128];
   int32_t status;

   *comp = vcos_malloc(sizeof(COMPONENT_T), "il:comp");
   if(!*comp)
      return -1;

   memset(*comp, 0, sizeof(COMPONENT_T));

#define COMP_PREFIX "OMX.broadcom."

   status = vcos_event_flags_create(&(*comp)->event,"il:comp");
   vc_assert(status == VCOS_SUCCESS);
   status = vcos_semaphore_create(&(*comp)->sema, "il:comp", 1);
   vc_assert(status == VCOS_SUCCESS);
   (*comp)->client = client;

   vcos_snprintf((*comp)->name, sizeof((*comp)->name), "cl:%s", name);
   vcos_snprintf((*comp)->bufname, sizeof((*comp)->bufname), "cl:%s buffer", name);
   vcos_snprintf(component_name, sizeof(component_name), "%s%s", COMP_PREFIX, name);

   (*comp)->flags = flags;

   callbacks.EventHandler = ilclient_event_handler;
   callbacks.EmptyBufferDone = flags & ILCLIENT_ENABLE_INPUT_BUFFERS ? ilclient_empty_buffer_done : ilclient_empty_buffer_done_error;
   callbacks.FillBufferDone = flags & ILCLIENT_ENABLE_OUTPUT_BUFFERS ? ilclient_fill_buffer_done : ilclient_fill_buffer_done_error;

   error = OMX_GetHandle(&(*comp)->comp, component_name, *comp, &callbacks);

   if (error == OMX_ErrorNone)
   {
      OMX_UUIDTYPE uid;
      char name[128];
      OMX_VERSIONTYPE compVersion, specVersion;

      if(OMX_GetComponentVersion((*comp)->comp, name, &compVersion, &specVersion, &uid) == OMX_ErrorNone)
      {
         char *p = (char *) uid + strlen(COMP_PREFIX);

         vcos_snprintf((*comp)->name, sizeof((*comp)->name), "cl:%s", p);
         (*comp)->name[sizeof((*comp)->name)-1] = 0;
         vcos_snprintf((*comp)->bufname, sizeof((*comp)->bufname), "cl:%s buffer", p);
         (*comp)->bufname[sizeof((*comp)->bufname)-1] = 0;
      }

      if(flags & (ILCLIENT_DISABLE_ALL_PORTS | ILCLIENT_OUTPUT_ZERO_BUFFERS))
      {
         OMX_PORT_PARAM_TYPE ports;
         OMX_INDEXTYPE types[] = {OMX_IndexParamAudioInit, OMX_IndexParamVideoInit, OMX_IndexParamImageInit, OMX_IndexParamOtherInit};
         int i;

         ports.nSize = sizeof(OMX_PORT_PARAM_TYPE);
         ports.nVersion.nVersion = OMX_VERSION;

         for(i=0; i<4; i++)
         {
            OMX_ERRORTYPE error = OMX_GetParameter((*comp)->comp, types[i], &ports);
            if(error == OMX_ErrorNone)
            {
               uint32_t j;
               for(j=0; j<ports.nPorts; j++)
               {
                  if(flags & ILCLIENT_DISABLE_ALL_PORTS)
                     ilclient_disable_port(*comp, ports.nStartPortNumber+j);

                  if(flags & ILCLIENT_OUTPUT_ZERO_BUFFERS)
                  {
                     OMX_PARAM_PORTDEFINITIONTYPE portdef;
                     portdef.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
                     portdef.nVersion.nVersion = OMX_VERSION;
                     portdef.nPortIndex = ports.nStartPortNumber+j;
                     if(OMX_GetParameter((*comp)->comp, OMX_IndexParamPortDefinition, &portdef) == OMX_ErrorNone)
                     {
                        if(portdef.eDir == OMX_DirOutput && portdef.nBufferCountActual > 0)
                        {
                           portdef.nBufferCountActual = 0;
                           OMX_SetParameter((*comp)->comp, OMX_IndexParamPortDefinition, &portdef);
                        }
                     }
                  }
               }
            }
         }
      }
      return 0;
   }
   else
   {
      vcos_event_flags_delete(&(*comp)->event);
      vcos_semaphore_delete(&(*comp)->sema);
      vcos_free(*comp);
      *comp = NULL;
      return -1;
   }
}