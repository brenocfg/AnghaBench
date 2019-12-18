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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  VC_SERVICE_VCHI_STATUS_T ;

/* Variables and functions */
#define  VCHIQ_ERROR 130 
#define  VCHIQ_RETRY 129 
#define  VCHIQ_SUCCESS 128 
 int /*<<< orphan*/  VC_SERVICE_VCHI_SUCCESS ; 
 int /*<<< orphan*/  VC_SERVICE_VCHI_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  VC_SERVICE_VCHI_VCHIQ_ERROR ; 
 int /*<<< orphan*/  VC_SERVUCE_VCHI_RETRY ; 

VC_SERVICE_VCHI_STATUS_T vchi2service_status(int32_t x) {
   VC_SERVICE_VCHI_STATUS_T ret;
   switch(x) {
   case VCHIQ_SUCCESS:
      ret = VC_SERVICE_VCHI_SUCCESS; break;
   case VCHIQ_ERROR:
      ret = VC_SERVICE_VCHI_VCHIQ_ERROR; break;
   case VCHIQ_RETRY:
      ret = VC_SERVUCE_VCHI_RETRY; break;
   default:
      ret = VC_SERVICE_VCHI_UNKNOWN_ERROR;
   }
   return ret;
}