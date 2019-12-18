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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VC_URI_PARTS_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*,char const*,...) ; 
 char* vc_uri_fragment (int /*<<< orphan*/ *) ; 
 char* vc_uri_host (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_num_queries (int /*<<< orphan*/ *) ; 
 char* vc_uri_path (int /*<<< orphan*/ *) ; 
 char* vc_uri_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,char const**) ; 
 char* vc_uri_scheme (int /*<<< orphan*/ *) ; 
 char* vc_uri_userinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dump_uri(VC_URI_PARTS_T *uri)
{
   const char *str;
   uint32_t query_count, ii;

   str = vc_uri_scheme(uri);
   if (str)
      LOG_DEBUG(NULL, "Scheme: <%s>", str);

   str = vc_uri_userinfo(uri);
   if (str)
      LOG_DEBUG(NULL, "Userinfo: <%s>", str);

   str = vc_uri_host(uri);
   if (str)
      LOG_DEBUG(NULL, "Host: <%s>", str);

   str = vc_uri_port(uri);
   if (str)
      LOG_DEBUG(NULL, "Port: <%s>", str);

   str = vc_uri_path(uri);
   if (str)
      LOG_DEBUG(NULL, "Path: <%s>", str);

   query_count = vc_uri_num_queries(uri);
   for (ii = 0; ii < query_count; ii++)
   {
      const char *value;

      vc_uri_query(uri, ii, &str, &value);
      if (str)
      {
         if (value)
            LOG_DEBUG(NULL, "Query %d: <%s>=<%s>", ii, str, value);
         else
            LOG_DEBUG(NULL, "Query %d: <%s>", ii, str);
      }
   }

   str = vc_uri_fragment(uri);
   if (str)
      LOG_DEBUG(NULL, "Fragment: <%s>", str);
}