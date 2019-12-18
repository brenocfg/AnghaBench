#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_PACKETIZER_T ;
struct TYPE_3__ {scalar_t__ (* open ) (int /*<<< orphan*/ *) ;struct TYPE_3__* next; } ;
typedef  TYPE_1__ VC_PACKETIZER_REGISTRY_ENTRY_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 TYPE_1__* registry ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T vc_packetizer_load(VC_PACKETIZER_T *p_ctx)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   VC_PACKETIZER_REGISTRY_ENTRY_T *entry;

   /* Try all the packetizers until we find the right one */
   for (entry = registry; entry; entry = entry->next)
   {
      status = entry->open(p_ctx);
      if(status != VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED)
         break;
   }

   return status;
}