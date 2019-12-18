#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* scheme; char* host; char* port; char* userinfo; char* path; } ;
typedef  TYPE_1__ VC_URI_PARTS_T ;

/* Variables and functions */
 int duplicate_string (char*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* strrchr (char*,char) ; 
 int vc_uri_copy_base_path (TYPE_1__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  vc_uri_remove_double_dot_segments (char*) ; 
 int /*<<< orphan*/  vc_uri_remove_single_dot_segments (char*) ; 

bool vc_uri_merge( const VC_URI_PARTS_T *base_uri, VC_URI_PARTS_T *relative_uri )
{
   bool success = true;
   const char *relative_path;

   /* If scheme is already set, the URI is already absolute */
   if (relative_uri->scheme)
      return true;

   /* Otherwise, copy the base scheme */
   if (!duplicate_string(base_uri->scheme, &relative_uri->scheme))
      return false;

   /* If any of the network info is set, use the rest of the relative URI as-is */
   if (relative_uri->host || relative_uri->port || relative_uri->userinfo)
      return true;

   /* Otherwise, copy the base network info */
   if (!duplicate_string(base_uri->host, &relative_uri->host) ||
         !duplicate_string(base_uri->port, &relative_uri->port) ||
         !duplicate_string(base_uri->userinfo, &relative_uri->userinfo))
      return false;

   relative_path = relative_uri->path;

   if (!relative_path || !*relative_path)
   {
      /* No relative path (could be queries and/or fragment), so take base path */
      success = vc_uri_copy_base_path(base_uri, relative_uri);
   }
   else if (*relative_path != '/')
   {
      const char *base_path = base_uri->path;
      char *merged_path;
      char *slash;
      size_t len;

      /* Path is relative, merge in with base path */
      if (!base_path || !*base_path)
      {
         if (relative_uri->host || relative_uri->port || relative_uri->userinfo)
            base_path = "/";  /* Need a separator to split network info from path */
         else
            base_path = "";
      }

      len = strlen(base_path) + strlen(relative_path) + 1;

      /* Allocate space for largest possible combined path */
      merged_path = (char *)malloc(len);
      if (!merged_path)
         return false;

      strncpy(merged_path, base_path, len);

      slash = strrchr(merged_path, '/');  /* Note: reverse search */
      if (*relative_path == ';')
      {
         char *semi;

         /* Relative path is just parameters, so remove any base parameters in final segment */
         if (!slash)
            slash = merged_path;
         semi = strchr(slash, ';');
         if (semi)
            semi[0] = '\0';
      } else {
         /* Remove final segment */
         if (slash)
            slash[1] = '\0';
         else
            merged_path[0] = '\0';
      }
      strncat(merged_path, relative_path, len - strlen(merged_path) - 1);

      vc_uri_remove_single_dot_segments(merged_path);
      vc_uri_remove_double_dot_segments(merged_path);

      success = duplicate_string(merged_path, &relative_uri->path);

      free(merged_path);
   }
   /* Otherwise path is absolute, which can be left as-is */

   return success;
}