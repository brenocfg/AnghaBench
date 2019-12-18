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
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHIQ_BULK_MODE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHI_MEM_HANDLE_INVALID ; 
 int /*<<< orphan*/  vchiq_bulk_receive_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

VCHIQ_STATUS_T
vchiq_bulk_receive(VCHIQ_SERVICE_HANDLE_T handle,
   void *data,
   int size,
   void *userdata,
   VCHIQ_BULK_MODE_T mode)
{
   return vchiq_bulk_receive_handle(handle, VCHI_MEM_HANDLE_INVALID, data, size, userdata, mode, NULL);
}