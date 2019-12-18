#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_12__ {size_t element_count; TYPE_1__* elements; int /*<<< orphan*/  commit_count; } ;
typedef  TYPE_4__ WFC_SCENE_T ;
struct TYPE_14__ {int /*<<< orphan*/  type; } ;
struct TYPE_11__ {void* ptr; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_13__ {size_t flags; TYPE_7__ header; int /*<<< orphan*/  scene; TYPE_3__ scene_taken_data; TYPE_2__ scene_taken_cb; int /*<<< orphan*/  context; } ;
typedef  TYPE_5__ WFC_IPC_MSG_COMMIT_SCENE_T ;
typedef  int /*<<< orphan*/ * WFC_CALLBACK_T ;
typedef  int /*<<< orphan*/  WFCContext ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_9__ {int /*<<< orphan*/  source_stream; } ;

/* Variables and functions */
 size_t VCOS_ENOSYS ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_IPC_MSG_COMMIT_SCENE ; 
 size_t WFC_SERVER_COMMIT_WAIT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__ const*,int) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,...) ; 
 scalar_t__ wfc_client_ipc_sendwait (TYPE_7__*,int,size_t*,size_t*) ; 

uint32_t wfc_server_commit_scene(WFCContext context, const WFC_SCENE_T *scene,
      uint32_t flags, WFC_CALLBACK_T scene_taken_cb, void *scene_taken_data)
{
   WFC_IPC_MSG_COMMIT_SCENE_T msg;
   VCOS_STATUS_T status = VCOS_SUCCESS;
   uint32_t result = VCOS_ENOSYS;
   size_t result_len = sizeof(result);
   uint32_t i;

   vcos_log_trace("%s: context 0x%x commit %u elements %u flags 0x%x",
         VCOS_FUNCTION, context, scene->commit_count, scene->element_count, flags);
   for (i = 0; i < scene->element_count; i++)
   {
      vcos_log_trace("%s: element[%u] stream 0x%x", VCOS_FUNCTION, i, scene->elements[i].source_stream);
   }

   msg.header.type = WFC_IPC_MSG_COMMIT_SCENE;
   msg.context = context;
   msg.flags = flags;
   msg.scene_taken_cb.ptr = scene_taken_cb;
   msg.scene_taken_data.ptr = scene_taken_data;
   memcpy(&msg.scene, scene, sizeof(*scene));

   if (flags & WFC_SERVER_COMMIT_WAIT)
   {
      /* Caller will wait for callback, call cannot fail */
      vcos_assert(scene_taken_cb != NULL);
      vcos_assert(scene_taken_data != NULL);
   }
   else
   {
      /* Caller will not wait for callback, so need to at least wait for result. */
      vcos_assert(scene_taken_cb == NULL);
      vcos_assert(scene_taken_data == NULL);
   }

   status = wfc_client_ipc_sendwait(&msg.header, sizeof(msg), &result, &result_len);

   /* Override the result if the status was an error */
   if (status != VCOS_SUCCESS)
      result = status;

   return result;
}