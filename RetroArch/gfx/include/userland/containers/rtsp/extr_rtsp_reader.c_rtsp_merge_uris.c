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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  VC_URI_PARTS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ malloc (size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 size_t vc_uri_build (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/ * vc_uri_create () ; 
 int /*<<< orphan*/  vc_uri_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_parse (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vc_uri_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vc_uri_scheme (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtsp_merge_uris( VC_CONTAINER_T *p_ctx,
      const char *base_uri_str,
      const char *relative_uri_str,
      char **p_merged_uri_str)
{
   VC_URI_PARTS_T *base_uri = NULL;
   VC_URI_PARTS_T *relative_uri = NULL;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_OUT_OF_MEMORY;
   uint32_t merged_size;

   *p_merged_uri_str = NULL;
   relative_uri = vc_uri_create();
   if (!relative_uri) goto tidy_up;
   if (!vc_uri_parse(relative_uri, relative_uri_str))
   {
      status = VC_CONTAINER_ERROR_FORMAT_INVALID;
      goto tidy_up;
   }

   if (vc_uri_scheme(relative_uri) != NULL)
   {
      /* URI is absolute, not relative, so return it as the merged URI */
      size_t len = strlen(relative_uri_str);

      *p_merged_uri_str = (char *)malloc(len + 1);
      if (!*p_merged_uri_str) goto tidy_up;

      strncpy(*p_merged_uri_str, relative_uri_str, len);
      status = VC_CONTAINER_SUCCESS;
      goto tidy_up;
   }

   base_uri = vc_uri_create();
   if (!base_uri) goto tidy_up;
   if (!vc_uri_parse(base_uri, base_uri_str))
   {
      status = VC_CONTAINER_ERROR_FORMAT_INVALID;
      goto tidy_up;
   }

   /* Build up merged URI in relative_uri, using base_uri as necessary */
   if (!vc_uri_merge(base_uri, relative_uri)) goto tidy_up;

   merged_size = vc_uri_build(relative_uri, NULL, 0) + 1;
   *p_merged_uri_str = (char *)malloc(merged_size);
   if (!*p_merged_uri_str) goto tidy_up;

   vc_uri_build(relative_uri, *p_merged_uri_str, merged_size);

   status = VC_CONTAINER_SUCCESS;

tidy_up:
   if (base_uri) vc_uri_release(base_uri);
   if (relative_uri) vc_uri_release(relative_uri);
   if (status != VC_CONTAINER_SUCCESS)
      LOG_ERROR(p_ctx, "RTSP: Error merging URIs: %d", (int)status);
   return status;
}