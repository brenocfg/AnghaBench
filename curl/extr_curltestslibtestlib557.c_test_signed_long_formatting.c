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
struct TYPE_2__ {char* result; char* expected; int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int BUFSZ ; 
 int /*<<< orphan*/  curl_msprintf (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* sl_test ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int test_signed_long_formatting(void)
{
  int i, j;
  int num_slong_tests = 0;
  int failed = 0;

#if (SIZEOF_LONG == 2)

  i = 1; sl_test[i].num = 0x7FFFL; sl_test[i].expected = "32767";
  i++; sl_test[i].num = 0x7FFEL; sl_test[i].expected = "32766";
  i++; sl_test[i].num = 0x7FFDL; sl_test[i].expected = "32765";
  i++; sl_test[i].num = 0x7F00L; sl_test[i].expected = "32512";
  i++; sl_test[i].num = 0x07F0L; sl_test[i].expected = "2032";
  i++; sl_test[i].num = 0x007FL; sl_test[i].expected = "127";

  i++; sl_test[i].num = 0x7000L; sl_test[i].expected = "28672";
  i++; sl_test[i].num = 0x0700L; sl_test[i].expected = "1792";
  i++; sl_test[i].num = 0x0070L; sl_test[i].expected = "112";
  i++; sl_test[i].num = 0x0007L; sl_test[i].expected = "7";

  i++; sl_test[i].num = 0x5000L; sl_test[i].expected = "20480";
  i++; sl_test[i].num = 0x0500L; sl_test[i].expected = "1280";
  i++; sl_test[i].num = 0x0050L; sl_test[i].expected = "80";
  i++; sl_test[i].num = 0x0005L; sl_test[i].expected = "5";

  i++; sl_test[i].num = 0x0001L; sl_test[i].expected = "1";
  i++; sl_test[i].num = 0x0000L; sl_test[i].expected = "0";

  i++; sl_test[i].num = -0x7FFFL -1L; sl_test[i].expected = "-32768";
  i++; sl_test[i].num = -0x7FFEL -1L; sl_test[i].expected = "-32767";
  i++; sl_test[i].num = -0x7FFDL -1L; sl_test[i].expected = "-32766";
  i++; sl_test[i].num = -0x7F00L -1L; sl_test[i].expected = "-32513";
  i++; sl_test[i].num = -0x07F0L -1L; sl_test[i].expected = "-2033";
  i++; sl_test[i].num = -0x007FL -1L; sl_test[i].expected = "-128";

  i++; sl_test[i].num = -0x7000L -1L; sl_test[i].expected = "-28673";
  i++; sl_test[i].num = -0x0700L -1L; sl_test[i].expected = "-1793";
  i++; sl_test[i].num = -0x0070L -1L; sl_test[i].expected = "-113";
  i++; sl_test[i].num = -0x0007L -1L; sl_test[i].expected = "-8";

  i++; sl_test[i].num = -0x5000L -1L; sl_test[i].expected = "-20481";
  i++; sl_test[i].num = -0x0500L -1L; sl_test[i].expected = "-1281";
  i++; sl_test[i].num = -0x0050L -1L; sl_test[i].expected = "-81";
  i++; sl_test[i].num = -0x0005L -1L; sl_test[i].expected = "-6";

  i++; sl_test[i].num =  0x0000L -1L; sl_test[i].expected = "-1";

  num_slong_tests = i;

#elif (SIZEOF_LONG == 4)

  i = 1; sl_test[i].num = 0x7FFFFFFFL; sl_test[i].expected = "2147483647";
  i++; sl_test[i].num = 0x7FFFFFFEL; sl_test[i].expected = "2147483646";
  i++; sl_test[i].num = 0x7FFFFFFDL; sl_test[i].expected = "2147483645";
  i++; sl_test[i].num = 0x7FFF0000L; sl_test[i].expected = "2147418112";
  i++; sl_test[i].num = 0x00007FFFL; sl_test[i].expected = "32767";

  i++; sl_test[i].num = 0x7F000000L; sl_test[i].expected = "2130706432";
  i++; sl_test[i].num = 0x007F0000L; sl_test[i].expected = "8323072";
  i++; sl_test[i].num = 0x00007F00L; sl_test[i].expected = "32512";
  i++; sl_test[i].num = 0x0000007FL; sl_test[i].expected = "127";

  i++; sl_test[i].num = 0x70000000L; sl_test[i].expected = "1879048192";
  i++; sl_test[i].num = 0x07000000L; sl_test[i].expected = "117440512";
  i++; sl_test[i].num = 0x00700000L; sl_test[i].expected = "7340032";
  i++; sl_test[i].num = 0x00070000L; sl_test[i].expected = "458752";
  i++; sl_test[i].num = 0x00007000L; sl_test[i].expected = "28672";
  i++; sl_test[i].num = 0x00000700L; sl_test[i].expected = "1792";
  i++; sl_test[i].num = 0x00000070L; sl_test[i].expected = "112";
  i++; sl_test[i].num = 0x00000007L; sl_test[i].expected = "7";

  i++; sl_test[i].num = 0x50000000L; sl_test[i].expected = "1342177280";
  i++; sl_test[i].num = 0x05000000L; sl_test[i].expected = "83886080";
  i++; sl_test[i].num = 0x00500000L; sl_test[i].expected = "5242880";
  i++; sl_test[i].num = 0x00050000L; sl_test[i].expected = "327680";
  i++; sl_test[i].num = 0x00005000L; sl_test[i].expected = "20480";
  i++; sl_test[i].num = 0x00000500L; sl_test[i].expected = "1280";
  i++; sl_test[i].num = 0x00000050L; sl_test[i].expected = "80";
  i++; sl_test[i].num = 0x00000005L; sl_test[i].expected = "5";

  i++; sl_test[i].num = 0x00000001L; sl_test[i].expected = "1";
  i++; sl_test[i].num = 0x00000000L; sl_test[i].expected = "0";

  i++; sl_test[i].num = -0x7FFFFFFFL -1L; sl_test[i].expected = "-2147483648";
  i++; sl_test[i].num = -0x7FFFFFFEL -1L; sl_test[i].expected = "-2147483647";
  i++; sl_test[i].num = -0x7FFFFFFDL -1L; sl_test[i].expected = "-2147483646";
  i++; sl_test[i].num = -0x7FFF0000L -1L; sl_test[i].expected = "-2147418113";
  i++; sl_test[i].num = -0x00007FFFL -1L; sl_test[i].expected = "-32768";

  i++; sl_test[i].num = -0x7F000000L -1L; sl_test[i].expected = "-2130706433";
  i++; sl_test[i].num = -0x007F0000L -1L; sl_test[i].expected = "-8323073";
  i++; sl_test[i].num = -0x00007F00L -1L; sl_test[i].expected = "-32513";
  i++; sl_test[i].num = -0x0000007FL -1L; sl_test[i].expected = "-128";

  i++; sl_test[i].num = -0x70000000L -1L; sl_test[i].expected = "-1879048193";
  i++; sl_test[i].num = -0x07000000L -1L; sl_test[i].expected = "-117440513";
  i++; sl_test[i].num = -0x00700000L -1L; sl_test[i].expected = "-7340033";
  i++; sl_test[i].num = -0x00070000L -1L; sl_test[i].expected = "-458753";
  i++; sl_test[i].num = -0x00007000L -1L; sl_test[i].expected = "-28673";
  i++; sl_test[i].num = -0x00000700L -1L; sl_test[i].expected = "-1793";
  i++; sl_test[i].num = -0x00000070L -1L; sl_test[i].expected = "-113";
  i++; sl_test[i].num = -0x00000007L -1L; sl_test[i].expected = "-8";

  i++; sl_test[i].num = -0x50000000L -1L; sl_test[i].expected = "-1342177281";
  i++; sl_test[i].num = -0x05000000L -1L; sl_test[i].expected = "-83886081";
  i++; sl_test[i].num = -0x00500000L -1L; sl_test[i].expected = "-5242881";
  i++; sl_test[i].num = -0x00050000L -1L; sl_test[i].expected = "-327681";
  i++; sl_test[i].num = -0x00005000L -1L; sl_test[i].expected = "-20481";
  i++; sl_test[i].num = -0x00000500L -1L; sl_test[i].expected = "-1281";
  i++; sl_test[i].num = -0x00000050L -1L; sl_test[i].expected = "-81";
  i++; sl_test[i].num = -0x00000005L -1L; sl_test[i].expected = "-6";

  i++; sl_test[i].num =  0x00000000L -1L; sl_test[i].expected = "-1";

  num_slong_tests = i;

#elif (SIZEOF_LONG == 8)

  i = 1; sl_test[i].num = 0x7FFFFFFFFFFFFFFFL; sl_test[i].expected = "9223372036854775807";
  i++; sl_test[i].num = 0x7FFFFFFFFFFFFFFEL; sl_test[i].expected = "9223372036854775806";
  i++; sl_test[i].num = 0x7FFFFFFFFFFFFFFDL; sl_test[i].expected = "9223372036854775805";
  i++; sl_test[i].num = 0x7FFFFFFF00000000L; sl_test[i].expected = "9223372032559808512";
  i++; sl_test[i].num = 0x000000007FFFFFFFL; sl_test[i].expected = "2147483647";

  i++; sl_test[i].num = 0x7FFF000000000000L; sl_test[i].expected = "9223090561878065152";
  i++; sl_test[i].num = 0x00007FFF00000000L; sl_test[i].expected = "140733193388032";
  i++; sl_test[i].num = 0x000000007FFF0000L; sl_test[i].expected = "2147418112";
  i++; sl_test[i].num = 0x0000000000007FFFL; sl_test[i].expected = "32767";

  i++; sl_test[i].num = 0x7F00000000000000L; sl_test[i].expected = "9151314442816847872";
  i++; sl_test[i].num = 0x007F000000000000L; sl_test[i].expected = "35747322042253312";
  i++; sl_test[i].num = 0x00007F0000000000L; sl_test[i].expected = "139637976727552";
  i++; sl_test[i].num = 0x0000007F00000000L; sl_test[i].expected = "545460846592";
  i++; sl_test[i].num = 0x000000007F000000L; sl_test[i].expected = "2130706432";
  i++; sl_test[i].num = 0x00000000007F0000L; sl_test[i].expected = "8323072";
  i++; sl_test[i].num = 0x0000000000007F00L; sl_test[i].expected = "32512";
  i++; sl_test[i].num = 0x000000000000007FL; sl_test[i].expected = "127";

  i++; sl_test[i].num = 0x7000000000000000L; sl_test[i].expected = "8070450532247928832";
  i++; sl_test[i].num = 0x0700000000000000L; sl_test[i].expected = "504403158265495552";
  i++; sl_test[i].num = 0x0070000000000000L; sl_test[i].expected = "31525197391593472";
  i++; sl_test[i].num = 0x0007000000000000L; sl_test[i].expected = "1970324836974592";
  i++; sl_test[i].num = 0x0000700000000000L; sl_test[i].expected = "123145302310912";
  i++; sl_test[i].num = 0x0000070000000000L; sl_test[i].expected = "7696581394432";
  i++; sl_test[i].num = 0x0000007000000000L; sl_test[i].expected = "481036337152";
  i++; sl_test[i].num = 0x0000000700000000L; sl_test[i].expected = "30064771072";
  i++; sl_test[i].num = 0x0000000070000000L; sl_test[i].expected = "1879048192";
  i++; sl_test[i].num = 0x0000000007000000L; sl_test[i].expected = "117440512";
  i++; sl_test[i].num = 0x0000000000700000L; sl_test[i].expected = "7340032";
  i++; sl_test[i].num = 0x0000000000070000L; sl_test[i].expected = "458752";
  i++; sl_test[i].num = 0x0000000000007000L; sl_test[i].expected = "28672";
  i++; sl_test[i].num = 0x0000000000000700L; sl_test[i].expected = "1792";
  i++; sl_test[i].num = 0x0000000000000070L; sl_test[i].expected = "112";
  i++; sl_test[i].num = 0x0000000000000007L; sl_test[i].expected = "7";

  i++; sl_test[i].num = 0x0000000000000001L; sl_test[i].expected = "1";
  i++; sl_test[i].num = 0x0000000000000000L; sl_test[i].expected = "0";

  i++; sl_test[i].num = -0x7FFFFFFFFFFFFFFFL -1L; sl_test[i].expected = "-9223372036854775808";
  i++; sl_test[i].num = -0x7FFFFFFFFFFFFFFEL -1L; sl_test[i].expected = "-9223372036854775807";
  i++; sl_test[i].num = -0x7FFFFFFFFFFFFFFDL -1L; sl_test[i].expected = "-9223372036854775806";
  i++; sl_test[i].num = -0x7FFFFFFF00000000L -1L; sl_test[i].expected = "-9223372032559808513";
  i++; sl_test[i].num = -0x000000007FFFFFFFL -1L; sl_test[i].expected = "-2147483648";

  i++; sl_test[i].num = -0x7FFF000000000000L -1L; sl_test[i].expected = "-9223090561878065153";
  i++; sl_test[i].num = -0x00007FFF00000000L -1L; sl_test[i].expected = "-140733193388033";
  i++; sl_test[i].num = -0x000000007FFF0000L -1L; sl_test[i].expected = "-2147418113";
  i++; sl_test[i].num = -0x0000000000007FFFL -1L; sl_test[i].expected = "-32768";

  i++; sl_test[i].num = -0x7F00000000000000L -1L; sl_test[i].expected = "-9151314442816847873";
  i++; sl_test[i].num = -0x007F000000000000L -1L; sl_test[i].expected = "-35747322042253313";
  i++; sl_test[i].num = -0x00007F0000000000L -1L; sl_test[i].expected = "-139637976727553";
  i++; sl_test[i].num = -0x0000007F00000000L -1L; sl_test[i].expected = "-545460846593";
  i++; sl_test[i].num = -0x000000007F000000L -1L; sl_test[i].expected = "-2130706433";
  i++; sl_test[i].num = -0x00000000007F0000L -1L; sl_test[i].expected = "-8323073";
  i++; sl_test[i].num = -0x0000000000007F00L -1L; sl_test[i].expected = "-32513";
  i++; sl_test[i].num = -0x000000000000007FL -1L; sl_test[i].expected = "-128";

  i++; sl_test[i].num = -0x7000000000000000L -1L; sl_test[i].expected = "-8070450532247928833";
  i++; sl_test[i].num = -0x0700000000000000L -1L; sl_test[i].expected = "-504403158265495553";
  i++; sl_test[i].num = -0x0070000000000000L -1L; sl_test[i].expected = "-31525197391593473";
  i++; sl_test[i].num = -0x0007000000000000L -1L; sl_test[i].expected = "-1970324836974593";
  i++; sl_test[i].num = -0x0000700000000000L -1L; sl_test[i].expected = "-123145302310913";
  i++; sl_test[i].num = -0x0000070000000000L -1L; sl_test[i].expected = "-7696581394433";
  i++; sl_test[i].num = -0x0000007000000000L -1L; sl_test[i].expected = "-481036337153";
  i++; sl_test[i].num = -0x0000000700000000L -1L; sl_test[i].expected = "-30064771073";
  i++; sl_test[i].num = -0x0000000070000000L -1L; sl_test[i].expected = "-1879048193";
  i++; sl_test[i].num = -0x0000000007000000L -1L; sl_test[i].expected = "-117440513";
  i++; sl_test[i].num = -0x0000000000700000L -1L; sl_test[i].expected = "-7340033";
  i++; sl_test[i].num = -0x0000000000070000L -1L; sl_test[i].expected = "-458753";
  i++; sl_test[i].num = -0x0000000000007000L -1L; sl_test[i].expected = "-28673";
  i++; sl_test[i].num = -0x0000000000000700L -1L; sl_test[i].expected = "-1793";
  i++; sl_test[i].num = -0x0000000000000070L -1L; sl_test[i].expected = "-113";
  i++; sl_test[i].num = -0x0000000000000007L -1L; sl_test[i].expected = "-8";

  i++; sl_test[i].num =  0x0000000000000000L -1L; sl_test[i].expected = "-1";

  num_slong_tests = i;

#endif

  for(i = 1; i <= num_slong_tests; i++) {

    for(j = 0; j<BUFSZ; j++)
      sl_test[i].result[j] = 'X';
    sl_test[i].result[BUFSZ-1] = '\0';

    (void)curl_msprintf(sl_test[i].result, "%ld", sl_test[i].num);

    if(memcmp(sl_test[i].result,
              sl_test[i].expected,
              strlen(sl_test[i].expected))) {
      printf("signed long test #%.2d: Failed (Expected: %s Got: %s)\n",
             i, sl_test[i].expected, sl_test[i].result);
      failed++;
    }

  }

  if(!failed)
    printf("All curl_mprintf() signed long tests OK!\n");
  else
    printf("Some curl_mprintf() signed long tests Failed!\n");

  return failed;
}