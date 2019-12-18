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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  VC_URI_PARTS_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 char* TEST_STRING ; 
 int /*<<< orphan*/  vc_uri_build (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ vc_uri_fragment (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_host (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_num_queries (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_path (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,char const**) ; 
 scalar_t__ vc_uri_scheme (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_userinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_get_defaults(VC_URI_PARTS_T *uri)
{
   int error_count = 0;
   const char *name = NULL, *value = NULL;
   char buffer[1];

   if (vc_uri_scheme( uri ))
      error_count++;
   if (vc_uri_userinfo( uri ))
      error_count++;
   if (vc_uri_host( uri ))
      error_count++;
   if (vc_uri_port( uri ))
      error_count++;
   if (vc_uri_path( uri ))
      error_count++;
   if (vc_uri_fragment( uri ))
      error_count++;
   if (vc_uri_num_queries( uri ) != 0)
      error_count++;

   vc_uri_query( uri, 0, &name, &value );
   if (name != NULL || value != NULL)
      error_count++;

   if (vc_uri_build(uri, NULL, 0) != 0)
      error_count++;
   buffer[0] = ~*TEST_STRING;    /* Initialize with something */
   vc_uri_build(uri, buffer, sizeof(buffer));
   if (buffer[0] != '\0')        /* Expect empty string */
      error_count++;

   if (error_count)
      LOG_ERROR(NULL, "Getting default values gave unexpected values");

   return error_count;
}