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
 scalar_t__ check_accessors (int /*<<< orphan*/ *) ; 
 scalar_t__ check_build_parameters (int /*<<< orphan*/ *) ; 
 scalar_t__ check_get_defaults (int /*<<< orphan*/ *) ; 
 scalar_t__ check_null_uri_pointer () ; 
 scalar_t__ check_parse_parameters (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_parameter_validation(VC_URI_PARTS_T *uri)
{
   int error_count = 0;

   error_count += check_null_uri_pointer();
   error_count += check_get_defaults(uri);
   error_count += check_parse_parameters(uri);
   error_count += check_build_parameters(uri);
   error_count += check_accessors(uri);

   return error_count;
}