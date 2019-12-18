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
typedef  int /*<<< orphan*/  VC_URI_PARTS_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * TEST_NAME ; 
 int /*<<< orphan*/ * TEST_STRING ; 
 int /*<<< orphan*/ * TEST_VALUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ vc_uri_add_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* vc_uri_fragment (int /*<<< orphan*/ *) ; 
 char* vc_uri_host (int /*<<< orphan*/ *) ; 
 int vc_uri_num_queries (int /*<<< orphan*/ *) ; 
 char* vc_uri_path (int /*<<< orphan*/ *) ; 
 char* vc_uri_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_query (int /*<<< orphan*/ *,int,char const**,char const**) ; 
 char* vc_uri_scheme (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_fragment (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_host (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_scheme (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_userinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* vc_uri_userinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_accessors(VC_URI_PARTS_T *uri)
{
   int error_count = 0;
   const char *str;

   if (vc_uri_set_scheme( uri, TEST_STRING ))
   {
      str = vc_uri_scheme(uri);
      if (!str || strcmp(TEST_STRING, str))
         error_count++;
      if (!vc_uri_set_scheme( uri, NULL ))
         error_count++;
      if (vc_uri_scheme(uri))
         error_count++;
   } else
      error_count++;

   if (vc_uri_set_userinfo( uri, TEST_STRING ))
   {
      str = vc_uri_userinfo(uri);
      if (!str || strcmp(TEST_STRING, str))
         error_count++;
      if (!vc_uri_set_userinfo( uri, NULL ))
         error_count++;
      if (vc_uri_userinfo(uri))
         error_count++;
   } else
      error_count++;

   if (vc_uri_set_host( uri, TEST_STRING ))
   {
      str = vc_uri_host(uri);
      if (!str || strcmp(TEST_STRING, str))
         error_count++;
      if (!vc_uri_set_host( uri, NULL ))
         error_count++;
      if (vc_uri_host(uri))
         error_count++;
   } else
      error_count++;

   if (vc_uri_set_port( uri, TEST_STRING ))
   {
      str = vc_uri_port(uri);
      if (!str || strcmp(TEST_STRING, str))
         error_count++;
      if (!vc_uri_set_port( uri, NULL ))
         error_count++;
      if (vc_uri_port(uri))
         error_count++;
   } else
      error_count++;

   if (vc_uri_set_path( uri, TEST_STRING ))
   {
      str = vc_uri_path(uri);
      if (!str || strcmp(TEST_STRING, str))
         error_count++;
      if (!vc_uri_set_path( uri, NULL ))
         error_count++;
      if (vc_uri_path(uri))
         error_count++;
   } else
      error_count++;

   if (vc_uri_set_fragment( uri, TEST_STRING ))
   {
      str = vc_uri_fragment(uri);
      if (!str || strcmp(TEST_STRING, str))
         error_count++;
      if (!vc_uri_set_fragment( uri, NULL ))
         error_count++;
      if (vc_uri_fragment(uri))
         error_count++;
   } else
      error_count++;

   if (vc_uri_add_query( uri, NULL, NULL ))
      error_count++;
   if (vc_uri_add_query( uri, NULL, TEST_VALUE ))
      error_count++;
   if (!vc_uri_add_query( uri, TEST_STRING, NULL ))
      error_count++;
   if (!vc_uri_add_query( uri, TEST_NAME, TEST_VALUE ))
      error_count++;

   if (vc_uri_num_queries(uri) == 2)
   {
      const char *name = NULL, *value = NULL;

      vc_uri_query(uri, 0, &name, &value);
      if (!name || strcmp(TEST_STRING, name))
         error_count++;
      if (value)
         error_count++;

      vc_uri_query(uri, 1, &name, &value);
      if (!name || strcmp(TEST_NAME, name))
         error_count++;
      if (!value || strcmp(TEST_VALUE, value))
         error_count++;
   } else
      error_count++;

   if (error_count)
      LOG_ERROR(NULL, "Accessors failed");

   return error_count;
}