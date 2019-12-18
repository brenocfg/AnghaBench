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
 char TEST_CHAR ; 
 int /*<<< orphan*/ * TEST_STRING ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_build (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vc_uri_set_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_build_parameters(VC_URI_PARTS_T *uri)
{
   int error_count = 0;
   char buffer[1];

   vc_uri_set_path( uri, TEST_STRING );

   if (vc_uri_build( uri, NULL, 0 ) != strlen(TEST_STRING))
   {
      LOG_ERROR(NULL, "Retrieving URI length failed");
      error_count++;
   }

   buffer[0] = TEST_CHAR;
   if (vc_uri_build( uri, buffer, 1 ) != strlen(TEST_STRING))
   {
      LOG_ERROR(NULL, "Building URI to small buffer failed");
      error_count++;
   }
   if (buffer[0] != TEST_CHAR)
   {
      LOG_ERROR(NULL, "Building URI to small buffer modified buffer");
      error_count++;
   }

   vc_uri_set_path( uri, NULL );    /* Reset uri */

   return error_count;
}