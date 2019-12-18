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
 int curl_msnprintf (char*,int,char*,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ string_check (char*,char*) ; 

__attribute__((used)) static int test_weird_arguments(void)
{
  int errors = 0;
  char buf[256];
  int rc;

  /* MAX_PARAMETERS is 128, try exact 128! */
  rc = curl_msnprintf(buf, sizeof(buf),
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 1 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 2 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 3 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 4 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 5 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 6 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 7 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 8 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 9 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 10 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 11 */
                      "%d%d%d%d%d%d%d%d"     /* 8 */
                      ,
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 1 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 2 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 3 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 4 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 5 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 6 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 7 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 8 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 9 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 10 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 11 */
                      0, 1, 2, 3, 4, 5, 6, 7); /* 8 */

  if(rc != 128) {
    printf("curl_mprintf() returned %d and not 128!\n", rc);
    errors++;
  }

  errors += string_check(buf,
                         "0123456789" /* 10 */
                         "0123456789" /* 10 1 */
                         "0123456789" /* 10 2 */
                         "0123456789" /* 10 3 */
                         "0123456789" /* 10 4 */
                         "0123456789" /* 10 5 */
                         "0123456789" /* 10 6 */
                         "0123456789" /* 10 7 */
                         "0123456789" /* 10 8 */
                         "0123456789" /* 10 9 */
                         "0123456789" /* 10 10*/
                         "0123456789" /* 10 11 */
                         "01234567"   /* 8 */
    );

  /* MAX_PARAMETERS is 128, try more! */
  buf[0] = 0;
  rc = curl_msnprintf(buf, sizeof(buf),
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 1 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 2 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 3 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 4 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 5 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 6 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 7 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 8 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 9 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 10 */
                      "%d%d%d%d%d%d%d%d%d%d" /* 10 11 */
                      "%d%d%d%d%d%d%d%d%d"   /* 9 */
                      ,
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 1 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 2 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 3 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 4 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 5 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 6 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 7 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 8 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 9 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 10 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* 10 11 */
                      0, 1, 2, 3, 4, 5, 6, 7, 8);   /* 9 */

  if(rc != -1) {
    printf("curl_mprintf() returned %d and not -1!\n", rc);
    errors++;
  }

  errors += string_check(buf, "");

  if(errors)
    printf("Some curl_mprintf() weird arguments tests failed!\n");

  return errors;
}