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

/* Variables and functions */
 unsigned int HTTP_MAJOR_VERSION ; 
 unsigned int HTTP_MINOR_VERSION ; 
 unsigned int HTTP_STATUS_OK ; 
 unsigned int HTTP_STATUS_PARTIAL_CONTENT ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static bool io_http_successful_response_status(const char *status_line)
{
   unsigned int major_version, minor_version, status_code;

   /* coverity[secure_coding] String is null-terminated */
   if (sscanf(status_line, "HTTP/%u.%u %u", &major_version, &minor_version, &status_code) != 3)
   {
      LOG_ERROR(NULL, "HTTP: Invalid response status line:\n%s", status_line);
      return false;
   }

   if (major_version != HTTP_MAJOR_VERSION || minor_version != HTTP_MINOR_VERSION)
   {
      LOG_ERROR(NULL, "HTTP: Unexpected response HTTP version: %u.%u", major_version, minor_version);
      return false;
   }

   if (status_code != HTTP_STATUS_OK && status_code != HTTP_STATUS_PARTIAL_CONTENT)
   {
      LOG_ERROR(NULL, "HTTP: Response status unsuccessful:\n%s", status_line);
      return false;
   }

   return true;
}