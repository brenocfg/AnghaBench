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
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_1__* ul_test ; 

__attribute__((used)) static int test_unsigned_long_formatting(void)
{
  int i, j;
  int num_ulong_tests = 0;
  int failed = 0;

#if (SIZEOF_LONG == 2)

  i = 1; ul_test[i].num = 0xFFFFUL; ul_test[i].expected = "65535";
  i++; ul_test[i].num = 0xFF00UL; ul_test[i].expected = "65280";
  i++; ul_test[i].num = 0x00FFUL; ul_test[i].expected = "255";

  i++; ul_test[i].num = 0xF000UL; ul_test[i].expected = "61440";
  i++; ul_test[i].num = 0x0F00UL; ul_test[i].expected = "3840";
  i++; ul_test[i].num = 0x00F0UL; ul_test[i].expected = "240";
  i++; ul_test[i].num = 0x000FUL; ul_test[i].expected = "15";

  i++; ul_test[i].num = 0xC000UL; ul_test[i].expected = "49152";
  i++; ul_test[i].num = 0x0C00UL; ul_test[i].expected = "3072";
  i++; ul_test[i].num = 0x00C0UL; ul_test[i].expected = "192";
  i++; ul_test[i].num = 0x000CUL; ul_test[i].expected = "12";

  i++; ul_test[i].num = 0x0001UL; ul_test[i].expected = "1";
  i++; ul_test[i].num = 0x0000UL; ul_test[i].expected = "0";

  num_ulong_tests = i;

#elif (SIZEOF_LONG == 4)

  i = 1; ul_test[i].num = 0xFFFFFFFFUL; ul_test[i].expected = "4294967295";
  i++; ul_test[i].num = 0xFFFF0000UL; ul_test[i].expected = "4294901760";
  i++; ul_test[i].num = 0x0000FFFFUL; ul_test[i].expected = "65535";

  i++; ul_test[i].num = 0xFF000000UL; ul_test[i].expected = "4278190080";
  i++; ul_test[i].num = 0x00FF0000UL; ul_test[i].expected = "16711680";
  i++; ul_test[i].num = 0x0000FF00UL; ul_test[i].expected = "65280";
  i++; ul_test[i].num = 0x000000FFUL; ul_test[i].expected = "255";

  i++; ul_test[i].num = 0xF0000000UL; ul_test[i].expected = "4026531840";
  i++; ul_test[i].num = 0x0F000000UL; ul_test[i].expected = "251658240";
  i++; ul_test[i].num = 0x00F00000UL; ul_test[i].expected = "15728640";
  i++; ul_test[i].num = 0x000F0000UL; ul_test[i].expected = "983040";
  i++; ul_test[i].num = 0x0000F000UL; ul_test[i].expected = "61440";
  i++; ul_test[i].num = 0x00000F00UL; ul_test[i].expected = "3840";
  i++; ul_test[i].num = 0x000000F0UL; ul_test[i].expected = "240";
  i++; ul_test[i].num = 0x0000000FUL; ul_test[i].expected = "15";

  i++; ul_test[i].num = 0xC0000000UL; ul_test[i].expected = "3221225472";
  i++; ul_test[i].num = 0x0C000000UL; ul_test[i].expected = "201326592";
  i++; ul_test[i].num = 0x00C00000UL; ul_test[i].expected = "12582912";
  i++; ul_test[i].num = 0x000C0000UL; ul_test[i].expected = "786432";
  i++; ul_test[i].num = 0x0000C000UL; ul_test[i].expected = "49152";
  i++; ul_test[i].num = 0x00000C00UL; ul_test[i].expected = "3072";
  i++; ul_test[i].num = 0x000000C0UL; ul_test[i].expected = "192";
  i++; ul_test[i].num = 0x0000000CUL; ul_test[i].expected = "12";

  i++; ul_test[i].num = 0x00000001UL; ul_test[i].expected = "1";
  i++; ul_test[i].num = 0x00000000UL; ul_test[i].expected = "0";

  num_ulong_tests = i;

#elif (SIZEOF_LONG == 8)

  i = 1; ul_test[i].num = 0xFFFFFFFFFFFFFFFFUL; ul_test[i].expected = "18446744073709551615";
  i++; ul_test[i].num = 0xFFFFFFFF00000000UL; ul_test[i].expected = "18446744069414584320";
  i++; ul_test[i].num = 0x00000000FFFFFFFFUL; ul_test[i].expected = "4294967295";

  i++; ul_test[i].num = 0xFFFF000000000000UL; ul_test[i].expected = "18446462598732840960";
  i++; ul_test[i].num = 0x0000FFFF00000000UL; ul_test[i].expected = "281470681743360";
  i++; ul_test[i].num = 0x00000000FFFF0000UL; ul_test[i].expected = "4294901760";
  i++; ul_test[i].num = 0x000000000000FFFFUL; ul_test[i].expected = "65535";

  i++; ul_test[i].num = 0xFF00000000000000UL; ul_test[i].expected = "18374686479671623680";
  i++; ul_test[i].num = 0x00FF000000000000UL; ul_test[i].expected = "71776119061217280";
  i++; ul_test[i].num = 0x0000FF0000000000UL; ul_test[i].expected = "280375465082880";
  i++; ul_test[i].num = 0x000000FF00000000UL; ul_test[i].expected = "1095216660480";
  i++; ul_test[i].num = 0x00000000FF000000UL; ul_test[i].expected = "4278190080";
  i++; ul_test[i].num = 0x0000000000FF0000UL; ul_test[i].expected = "16711680";
  i++; ul_test[i].num = 0x000000000000FF00UL; ul_test[i].expected = "65280";
  i++; ul_test[i].num = 0x00000000000000FFUL; ul_test[i].expected = "255";

  i++; ul_test[i].num = 0xF000000000000000UL; ul_test[i].expected = "17293822569102704640";
  i++; ul_test[i].num = 0x0F00000000000000UL; ul_test[i].expected = "1080863910568919040";
  i++; ul_test[i].num = 0x00F0000000000000UL; ul_test[i].expected = "67553994410557440";
  i++; ul_test[i].num = 0x000F000000000000UL; ul_test[i].expected = "4222124650659840";
  i++; ul_test[i].num = 0x0000F00000000000UL; ul_test[i].expected = "263882790666240";
  i++; ul_test[i].num = 0x00000F0000000000UL; ul_test[i].expected = "16492674416640";
  i++; ul_test[i].num = 0x000000F000000000UL; ul_test[i].expected = "1030792151040";
  i++; ul_test[i].num = 0x0000000F00000000UL; ul_test[i].expected = "64424509440";
  i++; ul_test[i].num = 0x00000000F0000000UL; ul_test[i].expected = "4026531840";
  i++; ul_test[i].num = 0x000000000F000000UL; ul_test[i].expected = "251658240";
  i++; ul_test[i].num = 0x0000000000F00000UL; ul_test[i].expected = "15728640";
  i++; ul_test[i].num = 0x00000000000F0000UL; ul_test[i].expected = "983040";
  i++; ul_test[i].num = 0x000000000000F000UL; ul_test[i].expected = "61440";
  i++; ul_test[i].num = 0x0000000000000F00UL; ul_test[i].expected = "3840";
  i++; ul_test[i].num = 0x00000000000000F0UL; ul_test[i].expected = "240";
  i++; ul_test[i].num = 0x000000000000000FUL; ul_test[i].expected = "15";

  i++; ul_test[i].num = 0xC000000000000000UL; ul_test[i].expected = "13835058055282163712";
  i++; ul_test[i].num = 0x0C00000000000000UL; ul_test[i].expected = "864691128455135232";
  i++; ul_test[i].num = 0x00C0000000000000UL; ul_test[i].expected = "54043195528445952";
  i++; ul_test[i].num = 0x000C000000000000UL; ul_test[i].expected = "3377699720527872";
  i++; ul_test[i].num = 0x0000C00000000000UL; ul_test[i].expected = "211106232532992";
  i++; ul_test[i].num = 0x00000C0000000000UL; ul_test[i].expected = "13194139533312";
  i++; ul_test[i].num = 0x000000C000000000UL; ul_test[i].expected = "824633720832";
  i++; ul_test[i].num = 0x0000000C00000000UL; ul_test[i].expected = "51539607552";
  i++; ul_test[i].num = 0x00000000C0000000UL; ul_test[i].expected = "3221225472";
  i++; ul_test[i].num = 0x000000000C000000UL; ul_test[i].expected = "201326592";
  i++; ul_test[i].num = 0x0000000000C00000UL; ul_test[i].expected = "12582912";
  i++; ul_test[i].num = 0x00000000000C0000UL; ul_test[i].expected = "786432";
  i++; ul_test[i].num = 0x000000000000C000UL; ul_test[i].expected = "49152";
  i++; ul_test[i].num = 0x0000000000000C00UL; ul_test[i].expected = "3072";
  i++; ul_test[i].num = 0x00000000000000C0UL; ul_test[i].expected = "192";
  i++; ul_test[i].num = 0x000000000000000CUL; ul_test[i].expected = "12";

  i++; ul_test[i].num = 0x00000001UL; ul_test[i].expected = "1";
  i++; ul_test[i].num = 0x00000000UL; ul_test[i].expected = "0";

  num_ulong_tests = i;

#endif

  for(i = 1; i <= num_ulong_tests; i++) {

    for(j = 0; j<BUFSZ; j++)
      ul_test[i].result[j] = 'X';
    ul_test[i].result[BUFSZ-1] = '\0';

    (void)curl_msprintf(ul_test[i].result, "%lu", ul_test[i].num);

    if(memcmp(ul_test[i].result,
               ul_test[i].expected,
               strlen(ul_test[i].expected))) {
      printf("unsigned long test #%.2d: Failed (Expected: %s Got: %s)\n",
             i, ul_test[i].expected, ul_test[i].result);
      failed++;
    }

  }

  if(!failed)
    printf("All curl_mprintf() unsigned long tests OK!\n");
  else
    printf("Some curl_mprintf() unsigned long tests Failed!\n");

  return failed;
}