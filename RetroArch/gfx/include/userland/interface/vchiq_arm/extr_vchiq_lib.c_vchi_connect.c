#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ ** uint32_t ;
typedef  int int32_t ;
typedef  scalar_t__ VCHI_INSTANCE_T ;
typedef  int /*<<< orphan*/  VCHI_CONNECTION_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_SUCCESS ; 
 scalar_t__ vchiq_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_unused (int /*<<< orphan*/ ** const) ; 

int32_t
vchi_connect( VCHI_CONNECTION_T **connections,
   const uint32_t num_connections,
   VCHI_INSTANCE_T instance_handle )
{
   VCHIQ_STATUS_T status;

   vcos_unused(connections);
   vcos_unused(num_connections);

   status = vchiq_connect((VCHIQ_INSTANCE_T)instance_handle);

   return (status == VCHIQ_SUCCESS) ? 0 : -1;
}