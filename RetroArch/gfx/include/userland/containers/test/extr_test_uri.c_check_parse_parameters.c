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
 scalar_t__ vc_uri_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_parse_parameters(VC_URI_PARTS_T *uri)
{
   int error_count = 0;

   if (vc_uri_parse( uri, NULL ))
   {
      LOG_ERROR(NULL, "Parsing NULL URI failed");
      error_count++;
   }

   return error_count;
}