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
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_T ;
typedef  scalar_t__ VCHIQ_SERVICE_HANDLE_T ;
struct TYPE_5__ {size_t num_bytes; void* virt_addr; } ;
typedef  TYPE_2__ VCHIQ_DUMP_MEM_T ;

/* Variables and functions */
 int /*<<< orphan*/  RETRY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_IOC_DUMP_PHYS_MEM ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

VCHIQ_STATUS_T vchiq_dump_phys_mem( VCHIQ_SERVICE_HANDLE_T handle,
                             void *ptr,
                             size_t num_bytes )
{
   VCHIQ_SERVICE_T *service = (VCHIQ_SERVICE_T *)handle;
   VCHIQ_DUMP_MEM_T  dump_mem;
   int ret;

   if (!service)
      return VCHIQ_ERROR;

   dump_mem.virt_addr = ptr;
   dump_mem.num_bytes = num_bytes;

   RETRY(ret,ioctl(service->fd, VCHIQ_IOC_DUMP_PHYS_MEM, &dump_mem));
   return (ret >= 0) ? VCHIQ_SUCCESS : VCHIQ_ERROR;
}