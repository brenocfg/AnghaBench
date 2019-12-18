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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  VC_URI_PARTS_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  vc_uri_build (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static int check_uri(VC_URI_PARTS_T *uri, const char *expected)
{
   uint32_t built_len;
   char *built;

   built_len = vc_uri_build(uri, NULL, 0) + 1;
   built = (char *)malloc(built_len);
   if (!built)
   {
      LOG_ERROR(NULL, "*** Unexpected memory allocation failure: %d bytes", built_len);
      return 1;
   }

   vc_uri_build(uri, built, built_len);

   if (strcmp(built, expected) != 0)
   {
      LOG_ERROR(NULL, "*** Built URI <%s>\nexpected  <%s>", built, expected);
      free(built);
      return 1;
   }

   free(built);

   return 0;
}