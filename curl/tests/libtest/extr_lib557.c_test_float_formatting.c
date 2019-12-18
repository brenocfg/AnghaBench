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
 int /*<<< orphan*/  INT_MIN ; 
 double MAXIMIZE ; 
 int /*<<< orphan*/  curl_msnprintf (char*,int,char*,double,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ string_check (char*,char*) ; 
 scalar_t__ strlen_check (char*,int) ; 

__attribute__((used)) static int test_float_formatting(void)
{
  int errors = 0;
  char buf[512]; /* larger than max float size */
  curl_msnprintf(buf, sizeof(buf), "%f", 9.0);
  errors += string_check(buf, "9.000000");

  curl_msnprintf(buf, sizeof(buf), "%.1f", 9.1);
  errors += string_check(buf, "9.1");

  curl_msnprintf(buf, sizeof(buf), "%.2f", 9.1);
  errors += string_check(buf, "9.10");

  curl_msnprintf(buf, sizeof(buf), "%.0f", 9.1);
  errors += string_check(buf, "9");

  curl_msnprintf(buf, sizeof(buf), "%0f", 9.1);
  errors += string_check(buf, "9.100000");

  curl_msnprintf(buf, sizeof(buf), "%10f", 9.1);
  errors += string_check(buf, "  9.100000");

  curl_msnprintf(buf, sizeof(buf), "%10.3f", 9.1);
  errors += string_check(buf, "     9.100");

  curl_msnprintf(buf, sizeof(buf), "%-10.3f", 9.1);
  errors += string_check(buf, "9.100     ");

  curl_msnprintf(buf, sizeof(buf), "%-10.3f", 9.123456);
  errors += string_check(buf, "9.123     ");

  curl_msnprintf(buf, sizeof(buf), "%.-2f", 9.1);
  errors += string_check(buf, "9.100000");

  curl_msnprintf(buf, sizeof(buf), "%*f", 10, 9.1);
  errors += string_check(buf, "  9.100000");

  curl_msnprintf(buf, sizeof(buf), "%*f", 3, 9.1);
  errors += string_check(buf, "9.100000");

  curl_msnprintf(buf, sizeof(buf), "%*f", 6, 9.2987654);
  errors += string_check(buf, "9.298765");

  curl_msnprintf(buf, sizeof(buf), "%*f", 6, 9.298765);
  errors += string_check(buf, "9.298765");

  curl_msnprintf(buf, sizeof(buf), "%*f", 6, 9.29876);
  errors += string_check(buf, "9.298760");

  curl_msnprintf(buf, sizeof(buf), "%.*f", 6, 9.2987654);
  errors += string_check(buf, "9.298765");
  curl_msnprintf(buf, sizeof(buf), "%.*f", 5, 9.2987654);
  errors += string_check(buf, "9.29877");
  curl_msnprintf(buf, sizeof(buf), "%.*f", 4, 9.2987654);
  errors += string_check(buf, "9.2988");
  curl_msnprintf(buf, sizeof(buf), "%.*f", 3, 9.2987654);
  errors += string_check(buf, "9.299");
  curl_msnprintf(buf, sizeof(buf), "%.*f", 2, 9.2987654);
  errors += string_check(buf, "9.30");
  curl_msnprintf(buf, sizeof(buf), "%.*f", 1, 9.2987654);
  errors += string_check(buf, "9.3");
  curl_msnprintf(buf, sizeof(buf), "%.*f", 0, 9.2987654);
  errors += string_check(buf, "9");

  /* very large precisions easily turn into system specific outputs so we only
     check the output buffer length here as we know the internal limit */

  curl_msnprintf(buf, sizeof(buf), "%.*f", (1<<30), 9.2987654);
  errors += strlen_check(buf, 325);

  curl_msnprintf(buf, sizeof(buf), "%10000.10000f", 9.2987654);
  errors += strlen_check(buf, 325);

  curl_msnprintf(buf, sizeof(buf), "%240.10000f",
                 123456789123456789123456789.2987654);
  errors += strlen_check(buf, 325);

  /* check negative when used signed */
  curl_msnprintf(buf, sizeof(buf), "%*f", INT_MIN, 9.1);
  errors += string_check(buf, "9.100000");

  /* curl_msnprintf() limits a single float output to 325 bytes maximum
     width */
  curl_msnprintf(buf, sizeof(buf), "%*f", (1<<30), 9.1);
  errors += string_check(buf, "                                                                                                                                                                                                                                                                                                                             9.100000");
  curl_msnprintf(buf, sizeof(buf), "%100000f", 9.1);
  errors += string_check(buf, "                                                                                                                                                                                                                                                                                                                             9.100000");

  curl_msnprintf(buf, sizeof(buf), "%f", MAXIMIZE);
  errors += strlen_check(buf, 317);

  curl_msnprintf(buf, 2, "%f", MAXIMIZE);
  errors += strlen_check(buf, 1);
  curl_msnprintf(buf, 3, "%f", MAXIMIZE);
  errors += strlen_check(buf, 2);
  curl_msnprintf(buf, 4, "%f", MAXIMIZE);
  errors += strlen_check(buf, 3);
  curl_msnprintf(buf, 5, "%f", MAXIMIZE);
  errors += strlen_check(buf, 4);
  curl_msnprintf(buf, 6, "%f", MAXIMIZE);
  errors += strlen_check(buf, 5);

  if(!errors)
    printf("All float strings tests OK!\n");
  else
    printf("test_float_formatting Failed!\n");

  return errors;
}