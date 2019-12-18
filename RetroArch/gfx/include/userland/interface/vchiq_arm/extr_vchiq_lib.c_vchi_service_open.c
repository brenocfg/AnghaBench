#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  params ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  VCHI_SERVICE_HANDLE_T ;
typedef  scalar_t__ VCHI_INSTANCE_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_8__ {short version; short version_min; int /*<<< orphan*/  userdata; int /*<<< orphan*/  fourcc; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_PARAMS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;
struct TYPE_7__ {scalar_t__ version_min; scalar_t__ version; } ;
struct TYPE_9__ {int /*<<< orphan*/  callback; TYPE_1__ version; int /*<<< orphan*/  callback_param; int /*<<< orphan*/  service_id; } ;
typedef  TYPE_3__ SERVICE_CREATION_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_SUCCESS ; 
 scalar_t__ create_service (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int32_t
vchi_service_open( VCHI_INSTANCE_T instance_handle,
   SERVICE_CREATION_T *setup,
   VCHI_SERVICE_HANDLE_T *handle )
{
   VCHIQ_SERVICE_PARAMS_T params;
   VCHIQ_STATUS_T status;

   memset(&params, 0, sizeof(params));
   params.fourcc = setup->service_id;
   params.userdata = setup->callback_param;
   params.version = (short)setup->version.version;
   params.version_min = (short)setup->version.version_min;

   status = create_service((VCHIQ_INSTANCE_T)instance_handle,
      &params,
      setup->callback,
      1/*open*/,
      (VCHIQ_SERVICE_HANDLE_T *)handle);

   return (status == VCHIQ_SUCCESS) ? 0 : -1;
}