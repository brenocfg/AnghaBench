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
typedef  int VC_SERVICE_VCHI_STATUS_T ;

/* Variables and functions */
#define  VCHIQ_ERROR 130 
#define  VCHIQ_RETRY 129 
#define  VCHIQ_SUCCESS 128 

const char* vchi2service_status_string(VC_SERVICE_VCHI_STATUS_T status) {
   const char* string = "";
   switch(status) {
   case VCHIQ_SUCCESS:
      string = "success"; break;
   case VCHIQ_ERROR:
      string = "vchiq error"; break;
   case VCHIQ_RETRY:
      string = "retry"; break;
   default:
      string = "unknown";
   }
   return string;
}