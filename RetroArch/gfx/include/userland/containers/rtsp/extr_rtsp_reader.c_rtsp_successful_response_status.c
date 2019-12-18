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
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 unsigned int RTSP_MAJOR_VERSION ; 
 unsigned int RTSP_MINOR_VERSION ; 
 unsigned int RTSP_STATUS_MULTIPLE_CHOICES ; 
 unsigned int RTSP_STATUS_OK ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static bool rtsp_successful_response_status( VC_CONTAINER_T *p_ctx,
      const char *status_line)
{
   unsigned int major_version, minor_version, status_code;

   /* coverity[secure_coding] String is null-terminated */
   if (sscanf(status_line, "RTSP/%u.%u %u", &major_version, &minor_version, &status_code) != 3)
   {
      LOG_ERROR(p_ctx, "RTSP: Invalid response status line:\n%s", status_line);
      return false;
   }

   if (major_version != RTSP_MAJOR_VERSION || minor_version != RTSP_MINOR_VERSION)
   {
      LOG_ERROR(p_ctx, "RTSP: Unexpected response RTSP version: %u.%u", major_version, minor_version);
      return false;
   }

   if (status_code < RTSP_STATUS_OK || status_code >= RTSP_STATUS_MULTIPLE_CHOICES)
   {
      LOG_ERROR(p_ctx, "RTSP: Response status unsuccessful:\n%s", status_line);
      return false;
   }

   return true;
}