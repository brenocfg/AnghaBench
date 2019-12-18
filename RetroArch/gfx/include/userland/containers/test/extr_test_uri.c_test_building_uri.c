#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_URI_PARTS_T ;
struct TYPE_3__ {char** queries; int /*<<< orphan*/  expected_uri; int /*<<< orphan*/  fragment; int /*<<< orphan*/  path; int /*<<< orphan*/  port; int /*<<< orphan*/  host; int /*<<< orphan*/  userinfo; int /*<<< orphan*/  scheme; } ;
typedef  TYPE_1__ BUILD_URI_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_INFO (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int check_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_uri (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_add_query (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  vc_uri_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_set_fragment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_set_host (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_set_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_set_port (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_set_scheme (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_set_userinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_building_uri(VC_URI_PARTS_T *uri, BUILD_URI_T *uri_data)
{
   const char **p_str;
   const char *name, *value;

   LOG_INFO(NULL, "Building URI <%s>", uri_data->expected_uri);

   vc_uri_clear(uri);

   if (!vc_uri_set_scheme(uri, uri_data->scheme))
   {
      LOG_ERROR(NULL, "*** Failed to set scheme");
      return 1;
   }

   if (!vc_uri_set_userinfo(uri, uri_data->userinfo))
   {
      LOG_ERROR(NULL, "*** Failed to set userinfo");
      return 1;
   }

   if (!vc_uri_set_host(uri, uri_data->host))
   {
      LOG_ERROR(NULL, "*** Failed to set host");
      return 1;
   }

   if (!vc_uri_set_port(uri, uri_data->port))
   {
      LOG_ERROR(NULL, "*** Failed to set port");
      return 1;
   }

   if (!vc_uri_set_path(uri, uri_data->path))
   {
      LOG_ERROR(NULL, "*** Failed to set path");
      return 1;
   }

   if (!vc_uri_set_fragment(uri, uri_data->fragment))
   {
      LOG_ERROR(NULL, "*** Failed to set fragment");
      return 1;
   }

   p_str = uri_data->queries;
   name = *p_str++;

   while (name)
   {
      value = *p_str++;
      if (!vc_uri_add_query(uri, name, value))
      {
         LOG_ERROR(NULL, "*** Failed to add query");
         return 1;
      }
      name = *p_str++;
   }

   dump_uri(uri);

   return check_uri(uri, uri_data->expected_uri);
}