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
 TYPE_1__* si_test ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int test_signed_int_formatting(void)
{
  int i, j;
  int num_sint_tests = 0;
  int failed = 0;

#if (SIZEOF_INT == 2)

  i = 1; si_test[i].num = 0x7FFF; si_test[i].expected = "32767";
  i++; si_test[i].num = 0x7FFE; si_test[i].expected = "32766";
  i++; si_test[i].num = 0x7FFD; si_test[i].expected = "32765";
  i++; si_test[i].num = 0x7F00; si_test[i].expected = "32512";
  i++; si_test[i].num = 0x07F0; si_test[i].expected = "2032";
  i++; si_test[i].num = 0x007F; si_test[i].expected = "127";

  i++; si_test[i].num = 0x7000; si_test[i].expected = "28672";
  i++; si_test[i].num = 0x0700; si_test[i].expected = "1792";
  i++; si_test[i].num = 0x0070; si_test[i].expected = "112";
  i++; si_test[i].num = 0x0007; si_test[i].expected = "7";

  i++; si_test[i].num = 0x5000; si_test[i].expected = "20480";
  i++; si_test[i].num = 0x0500; si_test[i].expected = "1280";
  i++; si_test[i].num = 0x0050; si_test[i].expected = "80";
  i++; si_test[i].num = 0x0005; si_test[i].expected = "5";

  i++; si_test[i].num = 0x0001; si_test[i].expected = "1";
  i++; si_test[i].num = 0x0000; si_test[i].expected = "0";

  i++; si_test[i].num = -0x7FFF -1; si_test[i].expected = "-32768";
  i++; si_test[i].num = -0x7FFE -1; si_test[i].expected = "-32767";
  i++; si_test[i].num = -0x7FFD -1; si_test[i].expected = "-32766";
  i++; si_test[i].num = -0x7F00 -1; si_test[i].expected = "-32513";
  i++; si_test[i].num = -0x07F0 -1; si_test[i].expected = "-2033";
  i++; si_test[i].num = -0x007F -1; si_test[i].expected = "-128";

  i++; si_test[i].num = -0x7000 -1; si_test[i].expected = "-28673";
  i++; si_test[i].num = -0x0700 -1; si_test[i].expected = "-1793";
  i++; si_test[i].num = -0x0070 -1; si_test[i].expected = "-113";
  i++; si_test[i].num = -0x0007 -1; si_test[i].expected = "-8";

  i++; si_test[i].num = -0x5000 -1; si_test[i].expected = "-20481";
  i++; si_test[i].num = -0x0500 -1; si_test[i].expected = "-1281";
  i++; si_test[i].num = -0x0050 -1; si_test[i].expected = "-81";
  i++; si_test[i].num = -0x0005 -1; si_test[i].expected = "-6";

  i++; si_test[i].num =  0x0000 -1; si_test[i].expected = "-1";

  num_sint_tests = i;

#elif (SIZEOF_INT == 4)

  i = 1; si_test[i].num = 0x7FFFFFFF; si_test[i].expected = "2147483647";
  i++; si_test[i].num = 0x7FFFFFFE; si_test[i].expected = "2147483646";
  i++; si_test[i].num = 0x7FFFFFFD; si_test[i].expected = "2147483645";
  i++; si_test[i].num = 0x7FFF0000; si_test[i].expected = "2147418112";
  i++; si_test[i].num = 0x00007FFF; si_test[i].expected = "32767";

  i++; si_test[i].num = 0x7F000000; si_test[i].expected = "2130706432";
  i++; si_test[i].num = 0x007F0000; si_test[i].expected = "8323072";
  i++; si_test[i].num = 0x00007F00; si_test[i].expected = "32512";
  i++; si_test[i].num = 0x0000007F; si_test[i].expected = "127";

  i++; si_test[i].num = 0x70000000; si_test[i].expected = "1879048192";
  i++; si_test[i].num = 0x07000000; si_test[i].expected = "117440512";
  i++; si_test[i].num = 0x00700000; si_test[i].expected = "7340032";
  i++; si_test[i].num = 0x00070000; si_test[i].expected = "458752";
  i++; si_test[i].num = 0x00007000; si_test[i].expected = "28672";
  i++; si_test[i].num = 0x00000700; si_test[i].expected = "1792";
  i++; si_test[i].num = 0x00000070; si_test[i].expected = "112";
  i++; si_test[i].num = 0x00000007; si_test[i].expected = "7";

  i++; si_test[i].num = 0x50000000; si_test[i].expected = "1342177280";
  i++; si_test[i].num = 0x05000000; si_test[i].expected = "83886080";
  i++; si_test[i].num = 0x00500000; si_test[i].expected = "5242880";
  i++; si_test[i].num = 0x00050000; si_test[i].expected = "327680";
  i++; si_test[i].num = 0x00005000; si_test[i].expected = "20480";
  i++; si_test[i].num = 0x00000500; si_test[i].expected = "1280";
  i++; si_test[i].num = 0x00000050; si_test[i].expected = "80";
  i++; si_test[i].num = 0x00000005; si_test[i].expected = "5";

  i++; si_test[i].num = 0x00000001; si_test[i].expected = "1";
  i++; si_test[i].num = 0x00000000; si_test[i].expected = "0";

  i++; si_test[i].num = -0x7FFFFFFF -1; si_test[i].expected = "-2147483648";
  i++; si_test[i].num = -0x7FFFFFFE -1; si_test[i].expected = "-2147483647";
  i++; si_test[i].num = -0x7FFFFFFD -1; si_test[i].expected = "-2147483646";
  i++; si_test[i].num = -0x7FFF0000 -1; si_test[i].expected = "-2147418113";
  i++; si_test[i].num = -0x00007FFF -1; si_test[i].expected = "-32768";

  i++; si_test[i].num = -0x7F000000 -1; si_test[i].expected = "-2130706433";
  i++; si_test[i].num = -0x007F0000 -1; si_test[i].expected = "-8323073";
  i++; si_test[i].num = -0x00007F00 -1; si_test[i].expected = "-32513";
  i++; si_test[i].num = -0x0000007F -1; si_test[i].expected = "-128";

  i++; si_test[i].num = -0x70000000 -1; si_test[i].expected = "-1879048193";
  i++; si_test[i].num = -0x07000000 -1; si_test[i].expected = "-117440513";
  i++; si_test[i].num = -0x00700000 -1; si_test[i].expected = "-7340033";
  i++; si_test[i].num = -0x00070000 -1; si_test[i].expected = "-458753";
  i++; si_test[i].num = -0x00007000 -1; si_test[i].expected = "-28673";
  i++; si_test[i].num = -0x00000700 -1; si_test[i].expected = "-1793";
  i++; si_test[i].num = -0x00000070 -1; si_test[i].expected = "-113";
  i++; si_test[i].num = -0x00000007 -1; si_test[i].expected = "-8";

  i++; si_test[i].num = -0x50000000 -1; si_test[i].expected = "-1342177281";
  i++; si_test[i].num = -0x05000000 -1; si_test[i].expected = "-83886081";
  i++; si_test[i].num = -0x00500000 -1; si_test[i].expected = "-5242881";
  i++; si_test[i].num = -0x00050000 -1; si_test[i].expected = "-327681";
  i++; si_test[i].num = -0x00005000 -1; si_test[i].expected = "-20481";
  i++; si_test[i].num = -0x00000500 -1; si_test[i].expected = "-1281";
  i++; si_test[i].num = -0x00000050 -1; si_test[i].expected = "-81";
  i++; si_test[i].num = -0x00000005 -1; si_test[i].expected = "-6";

  i++; si_test[i].num =  0x00000000 -1; si_test[i].expected = "-1";

  num_sint_tests = i;

#elif (SIZEOF_INT == 8)

  i = 1; si_test[i].num = 0x7FFFFFFFFFFFFFFF; si_test[i].expected = "9223372036854775807";
  i++; si_test[i].num = 0x7FFFFFFFFFFFFFFE; si_test[i].expected = "9223372036854775806";
  i++; si_test[i].num = 0x7FFFFFFFFFFFFFFD; si_test[i].expected = "9223372036854775805";
  i++; si_test[i].num = 0x7FFFFFFF00000000; si_test[i].expected = "9223372032559808512";
  i++; si_test[i].num = 0x000000007FFFFFFF; si_test[i].expected = "2147483647";

  i++; si_test[i].num = 0x7FFF000000000000; si_test[i].expected = "9223090561878065152";
  i++; si_test[i].num = 0x00007FFF00000000; si_test[i].expected = "140733193388032";
  i++; si_test[i].num = 0x000000007FFF0000; si_test[i].expected = "2147418112";
  i++; si_test[i].num = 0x0000000000007FFF; si_test[i].expected = "32767";

  i++; si_test[i].num = 0x7F00000000000000; si_test[i].expected = "9151314442816847872";
  i++; si_test[i].num = 0x007F000000000000; si_test[i].expected = "35747322042253312";
  i++; si_test[i].num = 0x00007F0000000000; si_test[i].expected = "139637976727552";
  i++; si_test[i].num = 0x0000007F00000000; si_test[i].expected = "545460846592";
  i++; si_test[i].num = 0x000000007F000000; si_test[i].expected = "2130706432";
  i++; si_test[i].num = 0x00000000007F0000; si_test[i].expected = "8323072";
  i++; si_test[i].num = 0x0000000000007F00; si_test[i].expected = "32512";
  i++; si_test[i].num = 0x000000000000007F; si_test[i].expected = "127";

  i++; si_test[i].num = 0x7000000000000000; si_test[i].expected = "8070450532247928832";
  i++; si_test[i].num = 0x0700000000000000; si_test[i].expected = "504403158265495552";
  i++; si_test[i].num = 0x0070000000000000; si_test[i].expected = "31525197391593472";
  i++; si_test[i].num = 0x0007000000000000; si_test[i].expected = "1970324836974592";
  i++; si_test[i].num = 0x0000700000000000; si_test[i].expected = "123145302310912";
  i++; si_test[i].num = 0x0000070000000000; si_test[i].expected = "7696581394432";
  i++; si_test[i].num = 0x0000007000000000; si_test[i].expected = "481036337152";
  i++; si_test[i].num = 0x0000000700000000; si_test[i].expected = "30064771072";
  i++; si_test[i].num = 0x0000000070000000; si_test[i].expected = "1879048192";
  i++; si_test[i].num = 0x0000000007000000; si_test[i].expected = "117440512";
  i++; si_test[i].num = 0x0000000000700000; si_test[i].expected = "7340032";
  i++; si_test[i].num = 0x0000000000070000; si_test[i].expected = "458752";
  i++; si_test[i].num = 0x0000000000007000; si_test[i].expected = "28672";
  i++; si_test[i].num = 0x0000000000000700; si_test[i].expected = "1792";
  i++; si_test[i].num = 0x0000000000000070; si_test[i].expected = "112";
  i++; si_test[i].num = 0x0000000000000007; si_test[i].expected = "7";

  i++; si_test[i].num = 0x0000000000000001; si_test[i].expected = "1";
  i++; si_test[i].num = 0x0000000000000000; si_test[i].expected = "0";

  i++; si_test[i].num = -0x7FFFFFFFFFFFFFFF -1; si_test[i].expected = "-9223372036854775808";
  i++; si_test[i].num = -0x7FFFFFFFFFFFFFFE -1; si_test[i].expected = "-9223372036854775807";
  i++; si_test[i].num = -0x7FFFFFFFFFFFFFFD -1; si_test[i].expected = "-9223372036854775806";
  i++; si_test[i].num = -0x7FFFFFFF00000000 -1; si_test[i].expected = "-9223372032559808513";
  i++; si_test[i].num = -0x000000007FFFFFFF -1; si_test[i].expected = "-2147483648";

  i++; si_test[i].num = -0x7FFF000000000000 -1; si_test[i].expected = "-9223090561878065153";
  i++; si_test[i].num = -0x00007FFF00000000 -1; si_test[i].expected = "-140733193388033";
  i++; si_test[i].num = -0x000000007FFF0000 -1; si_test[i].expected = "-2147418113";
  i++; si_test[i].num = -0x0000000000007FFF -1; si_test[i].expected = "-32768";

  i++; si_test[i].num = -0x7F00000000000000 -1; si_test[i].expected = "-9151314442816847873";
  i++; si_test[i].num = -0x007F000000000000 -1; si_test[i].expected = "-35747322042253313";
  i++; si_test[i].num = -0x00007F0000000000 -1; si_test[i].expected = "-139637976727553";
  i++; si_test[i].num = -0x0000007F00000000 -1; si_test[i].expected = "-545460846593";
  i++; si_test[i].num = -0x000000007F000000 -1; si_test[i].expected = "-2130706433";
  i++; si_test[i].num = -0x00000000007F0000 -1; si_test[i].expected = "-8323073";
  i++; si_test[i].num = -0x0000000000007F00 -1; si_test[i].expected = "-32513";
  i++; si_test[i].num = -0x000000000000007F -1; si_test[i].expected = "-128";

  i++; si_test[i].num = -0x7000000000000000 -1; si_test[i].expected = "-8070450532247928833";
  i++; si_test[i].num = -0x0700000000000000 -1; si_test[i].expected = "-504403158265495553";
  i++; si_test[i].num = -0x0070000000000000 -1; si_test[i].expected = "-31525197391593473";
  i++; si_test[i].num = -0x0007000000000000 -1; si_test[i].expected = "-1970324836974593";
  i++; si_test[i].num = -0x0000700000000000 -1; si_test[i].expected = "-123145302310913";
  i++; si_test[i].num = -0x0000070000000000 -1; si_test[i].expected = "-7696581394433";
  i++; si_test[i].num = -0x0000007000000000 -1; si_test[i].expected = "-481036337153";
  i++; si_test[i].num = -0x0000000700000000 -1; si_test[i].expected = "-30064771073";
  i++; si_test[i].num = -0x0000000070000000 -1; si_test[i].expected = "-1879048193";
  i++; si_test[i].num = -0x0000000007000000 -1; si_test[i].expected = "-117440513";
  i++; si_test[i].num = -0x0000000000700000 -1; si_test[i].expected = "-7340033";
  i++; si_test[i].num = -0x0000000000070000 -1; si_test[i].expected = "-458753";
  i++; si_test[i].num = -0x0000000000007000 -1; si_test[i].expected = "-28673";
  i++; si_test[i].num = -0x0000000000000700 -1; si_test[i].expected = "-1793";
  i++; si_test[i].num = -0x0000000000000070 -1; si_test[i].expected = "-113";
  i++; si_test[i].num = -0x0000000000000007 -1; si_test[i].expected = "-8";

  i++; si_test[i].num =  0x0000000000000000 -1; si_test[i].expected = "-1";

  num_sint_tests = i;

#endif

  for(i = 1; i <= num_sint_tests; i++) {

    for(j = 0; j<BUFSZ; j++)
      si_test[i].result[j] = 'X';
    si_test[i].result[BUFSZ-1] = '\0';

    (void)curl_msprintf(si_test[i].result, "%d", si_test[i].num);

    if(memcmp(si_test[i].result,
              si_test[i].expected,
              strlen(si_test[i].expected))) {
      printf("signed int test #%.2d: Failed (Expected: %s Got: %s)\n",
             i, si_test[i].expected, si_test[i].result);
      failed++;
    }

  }

  if(!failed)
    printf("All curl_mprintf() signed int tests OK!\n");
  else
    printf("Some curl_mprintf() signed int tests Failed!\n");

  return failed;
}