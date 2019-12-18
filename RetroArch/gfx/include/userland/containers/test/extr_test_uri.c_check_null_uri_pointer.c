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

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 char TEST_CHAR ; 
 scalar_t__ vc_uri_add_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_build (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vc_uri_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_fragment (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_host (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_num_queries (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_parse (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vc_uri_path (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_release (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_scheme (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_fragment (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_host (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_scheme (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_set_userinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_userinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_null_uri_pointer(void)
{
   int error_count = 0;
   char buffer[1];

   /* Check NULL URI can be passed without failure to all routines */
   vc_uri_release( NULL );
   vc_uri_clear( NULL );
   if (vc_uri_parse( NULL, NULL ))
      error_count++;
   if (vc_uri_parse( NULL, "" ))
      error_count++;
   if (vc_uri_build( NULL, NULL, 0 ) != 0)
      error_count++;
   buffer[0] = TEST_CHAR;
   if (vc_uri_build( NULL, buffer, sizeof(buffer) ) != 0)
      error_count++;
   if (buffer[0] != TEST_CHAR)
      error_count++;
   if (vc_uri_scheme( NULL ))
      error_count++;
   if (vc_uri_userinfo( NULL ))
      error_count++;
   if (vc_uri_host( NULL ))
      error_count++;
   if (vc_uri_port( NULL ))
      error_count++;
   if (vc_uri_path( NULL ))
      error_count++;
   if (vc_uri_fragment( NULL ))
      error_count++;
   if (vc_uri_num_queries( NULL ) != 0)
      error_count++;
   vc_uri_query( NULL, 0, NULL, NULL );
   if (vc_uri_set_scheme( NULL, NULL ))
      error_count++;
   if (vc_uri_set_userinfo( NULL, NULL ))
      error_count++;
   if (vc_uri_set_host( NULL, NULL ))
      error_count++;
   if (vc_uri_set_port( NULL, NULL ))
      error_count++;
   if (vc_uri_set_path( NULL, NULL ))
      error_count++;
   if (vc_uri_set_fragment( NULL, NULL ))
      error_count++;
   if (vc_uri_add_query( NULL, NULL, NULL ))
      error_count++;

   if (error_count)
      LOG_ERROR(NULL, "NULL URI parameter testing failed");

   return error_count;
}