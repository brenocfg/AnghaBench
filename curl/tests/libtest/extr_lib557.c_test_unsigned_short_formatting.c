#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num; char* expected; char* result; } ;

/* Variables and functions */
 int BUFSZ ; 
 int /*<<< orphan*/  curl_msprintf (char*,char*,int) ; 
 scalar_t__ memcmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_1__* us_test ; 

__attribute__((used)) static int test_unsigned_short_formatting(void)
{
  int i, j;
  int num_ushort_tests = 0;
  int failed = 0;

#if (SIZEOF_SHORT == 1)

  i = 1; us_test[i].num = 0xFFU; us_test[i].expected = "256";
  i++; us_test[i].num = 0xF0U; us_test[i].expected = "240";
  i++; us_test[i].num = 0x0FU; us_test[i].expected = "15";

  i++; us_test[i].num = 0xE0U; us_test[i].expected = "224";
  i++; us_test[i].num = 0x0EU; us_test[i].expected = "14";

  i++; us_test[i].num = 0xC0U; us_test[i].expected = "192";
  i++; us_test[i].num = 0x0CU; us_test[i].expected = "12";

  i++; us_test[i].num = 0x01U; us_test[i].expected = "1";
  i++; us_test[i].num = 0x00U; us_test[i].expected = "0";

  num_ushort_tests = i;

#elif (SIZEOF_SHORT == 2)

  i = 1; us_test[i].num = 0xFFFFU; us_test[i].expected = "65535";
  i++; us_test[i].num = 0xFF00U; us_test[i].expected = "65280";
  i++; us_test[i].num = 0x00FFU; us_test[i].expected = "255";

  i++; us_test[i].num = 0xF000U; us_test[i].expected = "61440";
  i++; us_test[i].num = 0x0F00U; us_test[i].expected = "3840";
  i++; us_test[i].num = 0x00F0U; us_test[i].expected = "240";
  i++; us_test[i].num = 0x000FU; us_test[i].expected = "15";

  i++; us_test[i].num = 0xC000U; us_test[i].expected = "49152";
  i++; us_test[i].num = 0x0C00U; us_test[i].expected = "3072";
  i++; us_test[i].num = 0x00C0U; us_test[i].expected = "192";
  i++; us_test[i].num = 0x000CU; us_test[i].expected = "12";

  i++; us_test[i].num = 0x0001U; us_test[i].expected = "1";
  i++; us_test[i].num = 0x0000U; us_test[i].expected = "0";

  num_ushort_tests = i;

#elif (SIZEOF_SHORT == 4)

  i = 1; us_test[i].num = 0xFFFFFFFFU; us_test[i].expected = "4294967295";
  i++; us_test[i].num = 0xFFFF0000U; us_test[i].expected = "4294901760";
  i++; us_test[i].num = 0x0000FFFFU; us_test[i].expected = "65535";

  i++; us_test[i].num = 0xFF000000U; us_test[i].expected = "4278190080";
  i++; us_test[i].num = 0x00FF0000U; us_test[i].expected = "16711680";
  i++; us_test[i].num = 0x0000FF00U; us_test[i].expected = "65280";
  i++; us_test[i].num = 0x000000FFU; us_test[i].expected = "255";

  i++; us_test[i].num = 0xF0000000U; us_test[i].expected = "4026531840";
  i++; us_test[i].num = 0x0F000000U; us_test[i].expected = "251658240";
  i++; us_test[i].num = 0x00F00000U; us_test[i].expected = "15728640";
  i++; us_test[i].num = 0x000F0000U; us_test[i].expected = "983040";
  i++; us_test[i].num = 0x0000F000U; us_test[i].expected = "61440";
  i++; us_test[i].num = 0x00000F00U; us_test[i].expected = "3840";
  i++; us_test[i].num = 0x000000F0U; us_test[i].expected = "240";
  i++; us_test[i].num = 0x0000000FU; us_test[i].expected = "15";

  i++; us_test[i].num = 0xC0000000U; us_test[i].expected = "3221225472";
  i++; us_test[i].num = 0x0C000000U; us_test[i].expected = "201326592";
  i++; us_test[i].num = 0x00C00000U; us_test[i].expected = "12582912";
  i++; us_test[i].num = 0x000C0000U; us_test[i].expected = "786432";
  i++; us_test[i].num = 0x0000C000U; us_test[i].expected = "49152";
  i++; us_test[i].num = 0x00000C00U; us_test[i].expected = "3072";
  i++; us_test[i].num = 0x000000C0U; us_test[i].expected = "192";
  i++; us_test[i].num = 0x0000000CU; us_test[i].expected = "12";

  i++; us_test[i].num = 0x00000001U; us_test[i].expected = "1";
  i++; us_test[i].num = 0x00000000U; us_test[i].expected = "0";

  num_ushort_tests = i;

#endif

  for(i = 1; i <= num_ushort_tests; i++) {

    for(j = 0; j<BUFSZ; j++)
      us_test[i].result[j] = 'X';
    us_test[i].result[BUFSZ-1] = '\0';

    (void)curl_msprintf(us_test[i].result, "%hu", us_test[i].num);

    if(memcmp(us_test[i].result,
               us_test[i].expected,
               strlen(us_test[i].expected))) {
      printf("unsigned short test #%.2d: Failed (Expected: %s Got: %s)\n",
             i, us_test[i].expected, us_test[i].result);
      failed++;
    }

  }

  if(!failed)
    printf("All curl_mprintf() unsigned short tests OK!\n");
  else
    printf("Some curl_mprintf() unsigned short tests Failed!\n");

  return failed;
}