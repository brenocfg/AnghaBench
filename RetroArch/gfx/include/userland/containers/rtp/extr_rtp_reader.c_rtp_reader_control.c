#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int timestamp_base; int /*<<< orphan*/  flags; void* expected_ssrc; int /*<<< orphan*/  probation; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_10__ {TYPE_2__** tracks; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int VC_CONTAINER_CONTROL_T ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACK_SSRC_SET ; 
#define  VC_CONTAINER_CONTROL_SET_NEXT_SEQUENCE_NUMBER 130 
#define  VC_CONTAINER_CONTROL_SET_SOURCE_ID 129 
#define  VC_CONTAINER_CONTROL_SET_TIMESTAMP_BASE 128 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  init_sequence_number (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint32_t ; 
 void* va_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtp_reader_control( VC_CONTAINER_T *p_ctx,
                                                VC_CONTAINER_CONTROL_T operation,
                                                va_list args)
{
   VC_CONTAINER_STATUS_T status;
   VC_CONTAINER_TRACK_MODULE_T *t_module = p_ctx->tracks[0]->priv->module;

   switch (operation)
   {
   case VC_CONTAINER_CONTROL_SET_TIMESTAMP_BASE:
      {
         t_module->timestamp_base = va_arg(args, uint32_t);
         if (!t_module->timestamp_base)
            t_module->timestamp_base = 1;    /* Zero is used to mean "not set" */
         status = VC_CONTAINER_SUCCESS;
      }
      break;
   case VC_CONTAINER_CONTROL_SET_NEXT_SEQUENCE_NUMBER:
      {
         init_sequence_number(t_module, (uint16_t)va_arg(args, uint32_t));
         t_module->probation = 0;
         status = VC_CONTAINER_SUCCESS;
      }
      break;
   case VC_CONTAINER_CONTROL_SET_SOURCE_ID:
      {
         t_module->expected_ssrc = va_arg(args, uint32_t);
         SET_BIT(t_module->flags, TRACK_SSRC_SET);
         status = VC_CONTAINER_SUCCESS;
      }
      break;
   default:
      status = VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION;
   }

   return status;
}