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

/* Variables and functions */
 int /*<<< orphan*/  LC_NUMERIC ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ test_curl_off_t_formatting () ; 
 scalar_t__ test_float_formatting () ; 
 scalar_t__ test_signed_int_formatting () ; 
 scalar_t__ test_signed_long_formatting () ; 
 scalar_t__ test_signed_short_formatting () ; 
 scalar_t__ test_string_formatting () ; 
 scalar_t__ test_unsigned_int_formatting () ; 
 scalar_t__ test_unsigned_long_formatting () ; 
 scalar_t__ test_unsigned_short_formatting () ; 
 scalar_t__ test_weird_arguments () ; 

int test(char *URL)
{
  int errors = 0;
  (void)URL; /* not used */

#ifdef HAVE_SETLOCALE
  /*
   * The test makes assumptions about the numeric locale (specifically,
   * RADIXCHAR) so set it to a known working (and portable) one.
   */
  setlocale(LC_NUMERIC, "C");
#endif

  errors += test_weird_arguments();

  errors += test_unsigned_short_formatting();

  errors += test_signed_short_formatting();

  errors += test_unsigned_int_formatting();

  errors += test_signed_int_formatting();

  errors += test_unsigned_long_formatting();

  errors += test_signed_long_formatting();

  errors += test_curl_off_t_formatting();

  errors += test_string_formatting();

  errors += test_float_formatting();

  if(errors)
    return TEST_ERR_MAJOR_BAD;
  else
    return 0;
}