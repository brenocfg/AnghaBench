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
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  LOG_INFO (int /*<<< orphan*/ *,char*,char const*) ; 
 int check_uri (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dump_uri (int /*<<< orphan*/ *) ; 
 int vc_uri_parse (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int test_parsing_uri(VC_URI_PARTS_T *uri, const char *original, const char *expected)
{
   bool parsed;

   LOG_INFO(NULL, "URI: <%s>", original);

   parsed = vc_uri_parse( uri, original );
   if (!parsed)
   {
      LOG_ERROR(NULL, "*** Expected <%s> to parse, but it didn't", original);
      return 1;
   }

   dump_uri(uri);

   return check_uri(uri, expected ? expected : original);
}