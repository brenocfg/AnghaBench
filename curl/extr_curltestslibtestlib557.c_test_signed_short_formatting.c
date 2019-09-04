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
 TYPE_1__* ss_test ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int test_signed_short_formatting(void)
{
  int i, j;
  int num_sshort_tests = 0;
  int failed = 0;

#if (SIZEOF_SHORT == 1)

  i = 1; ss_test[i].num = 0x7F; ss_test[i].expected = "127";

  i++; ss_test[i].num = 0x70; ss_test[i].expected = "112";
  i++; ss_test[i].num = 0x07; ss_test[i].expected = "7";

  i++; ss_test[i].num = 0x50; ss_test[i].expected = "80";
  i++; ss_test[i].num = 0x05; ss_test[i].expected = "5";

  i++; ss_test[i].num = 0x01; ss_test[i].expected = "1";
  i++; ss_test[i].num = 0x00; ss_test[i].expected = "0";

  i++; ss_test[i].num = -0x7F -1; ss_test[i].expected = "-128";

  i++; ss_test[i].num = -0x70 -1; ss_test[i].expected = "-113";
  i++; ss_test[i].num = -0x07 -1; ss_test[i].expected = "-8";

  i++; ss_test[i].num = -0x50 -1; ss_test[i].expected = "-81";
  i++; ss_test[i].num = -0x05 -1; ss_test[i].expected = "-6";

  i++; ss_test[i].num =  0x00 -1; ss_test[i].expected = "-1";

  num_sshort_tests = i;

#elif (SIZEOF_SHORT == 2)

  i = 1; ss_test[i].num = 0x7FFF; ss_test[i].expected = "32767";
  i++; ss_test[i].num = 0x7FFE; ss_test[i].expected = "32766";
  i++; ss_test[i].num = 0x7FFD; ss_test[i].expected = "32765";
  i++; ss_test[i].num = 0x7F00; ss_test[i].expected = "32512";
  i++; ss_test[i].num = 0x07F0; ss_test[i].expected = "2032";
  i++; ss_test[i].num = 0x007F; ss_test[i].expected = "127";

  i++; ss_test[i].num = 0x7000; ss_test[i].expected = "28672";
  i++; ss_test[i].num = 0x0700; ss_test[i].expected = "1792";
  i++; ss_test[i].num = 0x0070; ss_test[i].expected = "112";
  i++; ss_test[i].num = 0x0007; ss_test[i].expected = "7";

  i++; ss_test[i].num = 0x5000; ss_test[i].expected = "20480";
  i++; ss_test[i].num = 0x0500; ss_test[i].expected = "1280";
  i++; ss_test[i].num = 0x0050; ss_test[i].expected = "80";
  i++; ss_test[i].num = 0x0005; ss_test[i].expected = "5";

  i++; ss_test[i].num = 0x0001; ss_test[i].expected = "1";
  i++; ss_test[i].num = 0x0000; ss_test[i].expected = "0";

  i++; ss_test[i].num = -0x7FFF -1; ss_test[i].expected = "-32768";
  i++; ss_test[i].num = -0x7FFE -1; ss_test[i].expected = "-32767";
  i++; ss_test[i].num = -0x7FFD -1; ss_test[i].expected = "-32766";
  i++; ss_test[i].num = -0x7F00 -1; ss_test[i].expected = "-32513";
  i++; ss_test[i].num = -0x07F0 -1; ss_test[i].expected = "-2033";
  i++; ss_test[i].num = -0x007F -1; ss_test[i].expected = "-128";

  i++; ss_test[i].num = -0x7000 -1; ss_test[i].expected = "-28673";
  i++; ss_test[i].num = -0x0700 -1; ss_test[i].expected = "-1793";
  i++; ss_test[i].num = -0x0070 -1; ss_test[i].expected = "-113";
  i++; ss_test[i].num = -0x0007 -1; ss_test[i].expected = "-8";

  i++; ss_test[i].num = -0x5000 -1; ss_test[i].expected = "-20481";
  i++; ss_test[i].num = -0x0500 -1; ss_test[i].expected = "-1281";
  i++; ss_test[i].num = -0x0050 -1; ss_test[i].expected = "-81";
  i++; ss_test[i].num = -0x0005 -1; ss_test[i].expected = "-6";

  i++; ss_test[i].num =  0x0000 -1; ss_test[i].expected = "-1";

  num_sshort_tests = i;

#elif (SIZEOF_SHORT == 4)

  i = 1; ss_test[i].num = 0x7FFFFFFF; ss_test[i].expected = "2147483647";
  i++; ss_test[i].num = 0x7FFFFFFE; ss_test[i].expected = "2147483646";
  i++; ss_test[i].num = 0x7FFFFFFD; ss_test[i].expected = "2147483645";
  i++; ss_test[i].num = 0x7FFF0000; ss_test[i].expected = "2147418112";
  i++; ss_test[i].num = 0x00007FFF; ss_test[i].expected = "32767";

  i++; ss_test[i].num = 0x7F000000; ss_test[i].expected = "2130706432";
  i++; ss_test[i].num = 0x007F0000; ss_test[i].expected = "8323072";
  i++; ss_test[i].num = 0x00007F00; ss_test[i].expected = "32512";
  i++; ss_test[i].num = 0x0000007F; ss_test[i].expected = "127";

  i++; ss_test[i].num = 0x70000000; ss_test[i].expected = "1879048192";
  i++; ss_test[i].num = 0x07000000; ss_test[i].expected = "117440512";
  i++; ss_test[i].num = 0x00700000; ss_test[i].expected = "7340032";
  i++; ss_test[i].num = 0x00070000; ss_test[i].expected = "458752";
  i++; ss_test[i].num = 0x00007000; ss_test[i].expected = "28672";
  i++; ss_test[i].num = 0x00000700; ss_test[i].expected = "1792";
  i++; ss_test[i].num = 0x00000070; ss_test[i].expected = "112";
  i++; ss_test[i].num = 0x00000007; ss_test[i].expected = "7";

  i++; ss_test[i].num = 0x50000000; ss_test[i].expected = "1342177280";
  i++; ss_test[i].num = 0x05000000; ss_test[i].expected = "83886080";
  i++; ss_test[i].num = 0x00500000; ss_test[i].expected = "5242880";
  i++; ss_test[i].num = 0x00050000; ss_test[i].expected = "327680";
  i++; ss_test[i].num = 0x00005000; ss_test[i].expected = "20480";
  i++; ss_test[i].num = 0x00000500; ss_test[i].expected = "1280";
  i++; ss_test[i].num = 0x00000050; ss_test[i].expected = "80";
  i++; ss_test[i].num = 0x00000005; ss_test[i].expected = "5";

  i++; ss_test[i].num = 0x00000001; ss_test[i].expected = "1";
  i++; ss_test[i].num = 0x00000000; ss_test[i].expected = "0";

  i++; ss_test[i].num = -0x7FFFFFFF -1; ss_test[i].expected = "-2147483648";
  i++; ss_test[i].num = -0x7FFFFFFE -1; ss_test[i].expected = "-2147483647";
  i++; ss_test[i].num = -0x7FFFFFFD -1; ss_test[i].expected = "-2147483646";
  i++; ss_test[i].num = -0x7FFF0000 -1; ss_test[i].expected = "-2147418113";
  i++; ss_test[i].num = -0x00007FFF -1; ss_test[i].expected = "-32768";

  i++; ss_test[i].num = -0x7F000000 -1; ss_test[i].expected = "-2130706433";
  i++; ss_test[i].num = -0x007F0000 -1; ss_test[i].expected = "-8323073";
  i++; ss_test[i].num = -0x00007F00 -1; ss_test[i].expected = "-32513";
  i++; ss_test[i].num = -0x0000007F -1; ss_test[i].expected = "-128";

  i++; ss_test[i].num = -0x70000000 -1; ss_test[i].expected = "-1879048193";
  i++; ss_test[i].num = -0x07000000 -1; ss_test[i].expected = "-117440513";
  i++; ss_test[i].num = -0x00700000 -1; ss_test[i].expected = "-7340033";
  i++; ss_test[i].num = -0x00070000 -1; ss_test[i].expected = "-458753";
  i++; ss_test[i].num = -0x00007000 -1; ss_test[i].expected = "-28673";
  i++; ss_test[i].num = -0x00000700 -1; ss_test[i].expected = "-1793";
  i++; ss_test[i].num = -0x00000070 -1; ss_test[i].expected = "-113";
  i++; ss_test[i].num = -0x00000007 -1; ss_test[i].expected = "-8";

  i++; ss_test[i].num = -0x50000000 -1; ss_test[i].expected = "-1342177281";
  i++; ss_test[i].num = -0x05000000 -1; ss_test[i].expected = "-83886081";
  i++; ss_test[i].num = -0x00500000 -1; ss_test[i].expected = "-5242881";
  i++; ss_test[i].num = -0x00050000 -1; ss_test[i].expected = "-327681";
  i++; ss_test[i].num = -0x00005000 -1; ss_test[i].expected = "-20481";
  i++; ss_test[i].num = -0x00000500 -1; ss_test[i].expected = "-1281";
  i++; ss_test[i].num = -0x00000050 -1; ss_test[i].expected = "-81";
  i++; ss_test[i].num = -0x00000005 -1; ss_test[i].expected = "-6";

  i++; ss_test[i].num =  0x00000000 -1; ss_test[i].expected = "-1";

  num_sshort_tests = i;

#endif

  for(i = 1; i <= num_sshort_tests; i++) {

    for(j = 0; j<BUFSZ; j++)
      ss_test[i].result[j] = 'X';
    ss_test[i].result[BUFSZ-1] = '\0';

    (void)curl_msprintf(ss_test[i].result, "%hd", ss_test[i].num);

    if(memcmp(ss_test[i].result,
              ss_test[i].expected,
              strlen(ss_test[i].expected))) {
      printf("signed short test #%.2d: Failed (Expected: %s Got: %s)\n",
             i, ss_test[i].expected, ss_test[i].result);
      failed++;
    }

  }

  if(!failed)
    printf("All curl_mprintf() signed short tests OK!\n");
  else
    printf("Some curl_mprintf() signed short tests Failed!\n");

  return failed;
}