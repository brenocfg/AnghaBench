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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  curl_msnprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ string_check (char*,char*) ; 

__attribute__((used)) static int test_string_formatting(void)
{
  int errors = 0;
  char buf[256];
  curl_msnprintf(buf, sizeof(buf), "%0*d%s", 2, 9, "foo");
  errors += string_check(buf, "09foo");

  curl_msnprintf(buf, sizeof(buf), "%*.*s", 5, 2, "foo");
  errors += string_check(buf, "   fo");

  curl_msnprintf(buf, sizeof(buf), "%*.*s", 2, 5, "foo");
  errors += string_check(buf, "foo");

  curl_msnprintf(buf, sizeof(buf), "%*.*s", 0, 10, "foo");
  errors += string_check(buf, "foo");

  curl_msnprintf(buf, sizeof(buf), "%-10s", "foo");
  errors += string_check(buf, "foo       ");

  curl_msnprintf(buf, sizeof(buf), "%10s", "foo");
  errors += string_check(buf, "       foo");

  curl_msnprintf(buf, sizeof(buf), "%*.*s", -10, -10, "foo");
  errors += string_check(buf, "foo       ");

  if(!errors)
    printf("All curl_mprintf() strings tests OK!\n");
  else
    printf("Some curl_mprintf() string tests Failed!\n");

  return errors;
}