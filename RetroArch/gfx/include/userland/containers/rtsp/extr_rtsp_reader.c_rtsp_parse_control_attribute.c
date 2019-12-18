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
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  rtsp_merge_uris (int /*<<< orphan*/ *,char const*,char const*,char**) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtsp_parse_control_attribute( VC_CONTAINER_T *p_ctx,
      const char *attribute,
      const char *base_uri_str,
      char **p_control_uri_str)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;

   /* control attribute format:
    *    <control URI>
    * The control URI is either absolute or relative to the base URI. If the
    * control URI is just an asterisk, the control URI matches the base URI. */

   if (!*attribute || strcmp(attribute, "*") == 0)
   {
      size_t len = strlen(base_uri_str);

      *p_control_uri_str = (char *)malloc(len + 1);
      if (!*p_control_uri_str)
      {
         LOG_ERROR(p_ctx, "RTSP: Failed to allocate control URI");
         return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
      }
      strncpy(*p_control_uri_str, base_uri_str, len);
   } else {
      status = rtsp_merge_uris(p_ctx, base_uri_str, attribute, p_control_uri_str);
   }

   return status;
}