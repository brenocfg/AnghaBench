#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_URI_PARTS_T ;
struct TYPE_7__ {char* before; int /*<<< orphan*/ * after; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  LOG_INFO (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  getchar () ; 
 TYPE_1__* test_build_uris ; 
 scalar_t__ test_building_uri (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* test_merge_uris ; 
 scalar_t__ test_merging_uri (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ test_parameter_validation (int /*<<< orphan*/ *) ; 
 TYPE_1__* test_parse_uris ; 
 scalar_t__ test_parsing_uri (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vc_uri_create () ; 
 int /*<<< orphan*/  vc_uri_release (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
   VC_URI_PARTS_T *uri;
   int error_count = 0;
   size_t ii;

   uri = vc_uri_create();
   if (!uri)
   {
      LOG_ERROR(NULL, "*** Failed to create URI structure.");
      return 1;
   }

   LOG_INFO(NULL, "Test parameter validation");
   error_count +=  test_parameter_validation(uri);

   LOG_INFO(NULL, "Test parsing URIs:");
   for (ii = 0; ii < ARRAY_SIZE(test_parse_uris); ii++)
   {
      error_count += test_parsing_uri(uri, test_parse_uris[ii].before, test_parse_uris[ii].after);
   }

   LOG_INFO(NULL, "Test building URIs:");
   for (ii = 0; ii < ARRAY_SIZE(test_build_uris); ii++)
   {
      error_count += test_building_uri(uri, &test_build_uris[ii]);
   }

   LOG_INFO(NULL, "Test merging URIs:");
   for (ii = 0; ii < ARRAY_SIZE(test_merge_uris); ii++)
   {
      error_count += test_merging_uri(uri, &test_merge_uris[ii]);
   }

   if (argc > 1)
   {
      LOG_INFO(NULL, "Test parsing URIs from command line:");

      while (argc-- > 1)
      {
         /* Test URIs passed on the command line are expected to parse and to
          * match themselves when rebuilt. */
         error_count += test_parsing_uri(uri, argv[argc], NULL);
      }
   }

   vc_uri_release(uri);

   if (error_count)
      LOG_ERROR(NULL, "*** %d errors reported", error_count);

#ifdef _MSC_VER
   LOG_INFO(NULL, "Press return to complete test.");
   getchar();
#endif

   return error_count;
}