#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  reader; } ;
typedef  TYPE_1__ VC_CONTAINER_TRACK_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
struct TYPE_6__ {char* value; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ RTSP_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  RTP_INFO_NAME ; 
 int /*<<< orphan*/  VC_CONTAINER_CONTROL_SET_NEXT_SEQUENCE_NUMBER ; 
 int /*<<< orphan*/  VC_CONTAINER_CONTROL_SET_TIMESTAMP_BASE ; 
 int /*<<< orphan*/  rtsp_parse_extract_parameter (char**,char**,char**) ; 
 int sscanf (char*,char*,...) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  vc_container_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vc_containers_list_find_entry (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void rtsp_store_rtp_info(VC_CONTAINERS_LIST_T *header_list,
      VC_CONTAINER_TRACK_MODULE_T *t_module )
{
   RTSP_HEADER_T header;
   char *ptr;

   header.name = RTP_INFO_NAME;
   if (!vc_containers_list_find_entry(header_list, &header))
      return;

   ptr = header.value;
   while (ptr && *ptr)
   {
      char *name;
      char *value;

      if (!rtsp_parse_extract_parameter(&ptr, &name, &value))
         continue;

      if (strcasecmp(name, "rtptime") == 0)
      {
         unsigned int timestamp_base = 0;

         /* coverity[secure_coding] String is null-terminated */
         if (sscanf(value, "%u", &timestamp_base) == 1)
            (void)vc_container_control(t_module->reader, VC_CONTAINER_CONTROL_SET_TIMESTAMP_BASE, timestamp_base);
      }
      else if (strcasecmp(name, "seq") == 0)
      {
         unsigned short int sequence_number = 0;

         /* coverity[secure_coding] String is null-terminated */
         if (sscanf(value, "%hu", &sequence_number) == 1)
            (void)vc_container_control(t_module->reader, VC_CONTAINER_CONTROL_SET_NEXT_SEQUENCE_NUMBER, (uint32_t)sequence_number);
      }
   }
}