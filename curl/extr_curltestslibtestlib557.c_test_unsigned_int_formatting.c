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
 TYPE_1__* ui_test ; 

__attribute__((used)) static int test_unsigned_int_formatting(void)
{
  int i, j;
  int num_uint_tests = 0;
  int failed = 0;

#if (SIZEOF_INT == 2)

  i = 1; ui_test[i].num = 0xFFFFU; ui_test[i].expected = "65535";
  i++; ui_test[i].num = 0xFF00U; ui_test[i].expected = "65280";
  i++; ui_test[i].num = 0x00FFU; ui_test[i].expected = "255";

  i++; ui_test[i].num = 0xF000U; ui_test[i].expected = "61440";
  i++; ui_test[i].num = 0x0F00U; ui_test[i].expected = "3840";
  i++; ui_test[i].num = 0x00F0U; ui_test[i].expected = "240";
  i++; ui_test[i].num = 0x000FU; ui_test[i].expected = "15";

  i++; ui_test[i].num = 0xC000U; ui_test[i].expected = "49152";
  i++; ui_test[i].num = 0x0C00U; ui_test[i].expected = "3072";
  i++; ui_test[i].num = 0x00C0U; ui_test[i].expected = "192";
  i++; ui_test[i].num = 0x000CU; ui_test[i].expected = "12";

  i++; ui_test[i].num = 0x0001U; ui_test[i].expected = "1";
  i++; ui_test[i].num = 0x0000U; ui_test[i].expected = "0";

  num_uint_tests = i;

#elif (SIZEOF_INT == 4)

  i = 1; ui_test[i].num = 0xFFFFFFFFU; ui_test[i].expected = "4294967295";
  i++; ui_test[i].num = 0xFFFF0000U; ui_test[i].expected = "4294901760";
  i++; ui_test[i].num = 0x0000FFFFU; ui_test[i].expected = "65535";

  i++; ui_test[i].num = 0xFF000000U; ui_test[i].expected = "4278190080";
  i++; ui_test[i].num = 0x00FF0000U; ui_test[i].expected = "16711680";
  i++; ui_test[i].num = 0x0000FF00U; ui_test[i].expected = "65280";
  i++; ui_test[i].num = 0x000000FFU; ui_test[i].expected = "255";

  i++; ui_test[i].num = 0xF0000000U; ui_test[i].expected = "4026531840";
  i++; ui_test[i].num = 0x0F000000U; ui_test[i].expected = "251658240";
  i++; ui_test[i].num = 0x00F00000U; ui_test[i].expected = "15728640";
  i++; ui_test[i].num = 0x000F0000U; ui_test[i].expected = "983040";
  i++; ui_test[i].num = 0x0000F000U; ui_test[i].expected = "61440";
  i++; ui_test[i].num = 0x00000F00U; ui_test[i].expected = "3840";
  i++; ui_test[i].num = 0x000000F0U; ui_test[i].expected = "240";
  i++; ui_test[i].num = 0x0000000FU; ui_test[i].expected = "15";

  i++; ui_test[i].num = 0xC0000000U; ui_test[i].expected = "3221225472";
  i++; ui_test[i].num = 0x0C000000U; ui_test[i].expected = "201326592";
  i++; ui_test[i].num = 0x00C00000U; ui_test[i].expected = "12582912";
  i++; ui_test[i].num = 0x000C0000U; ui_test[i].expected = "786432";
  i++; ui_test[i].num = 0x0000C000U; ui_test[i].expected = "49152";
  i++; ui_test[i].num = 0x00000C00U; ui_test[i].expected = "3072";
  i++; ui_test[i].num = 0x000000C0U; ui_test[i].expected = "192";
  i++; ui_test[i].num = 0x0000000CU; ui_test[i].expected = "12";

  i++; ui_test[i].num = 0x00000001U; ui_test[i].expected = "1";
  i++; ui_test[i].num = 0x00000000U; ui_test[i].expected = "0";

  num_uint_tests = i;

#elif (SIZEOF_INT == 8)

  /* !checksrc! disable LONGLINE all */
  i = 1; ui_test[i].num = 0xFFFFFFFFFFFFFFFFU; ui_test[i].expected = "18446744073709551615";
  i++; ui_test[i].num = 0xFFFFFFFF00000000U; ui_test[i].expected = "18446744069414584320";
  i++; ui_test[i].num = 0x00000000FFFFFFFFU; ui_test[i].expected = "4294967295";

  i++; ui_test[i].num = 0xFFFF000000000000U; ui_test[i].expected = "18446462598732840960";
  i++; ui_test[i].num = 0x0000FFFF00000000U; ui_test[i].expected = "281470681743360";
  i++; ui_test[i].num = 0x00000000FFFF0000U; ui_test[i].expected = "4294901760";
  i++; ui_test[i].num = 0x000000000000FFFFU; ui_test[i].expected = "65535";

  i++; ui_test[i].num = 0xFF00000000000000U; ui_test[i].expected = "18374686479671623680";
  i++; ui_test[i].num = 0x00FF000000000000U; ui_test[i].expected = "71776119061217280";
  i++; ui_test[i].num = 0x0000FF0000000000U; ui_test[i].expected = "280375465082880";
  i++; ui_test[i].num = 0x000000FF00000000U; ui_test[i].expected = "1095216660480";
  i++; ui_test[i].num = 0x00000000FF000000U; ui_test[i].expected = "4278190080";
  i++; ui_test[i].num = 0x0000000000FF0000U; ui_test[i].expected = "16711680";
  i++; ui_test[i].num = 0x000000000000FF00U; ui_test[i].expected = "65280";
  i++; ui_test[i].num = 0x00000000000000FFU; ui_test[i].expected = "255";

  i++; ui_test[i].num = 0xF000000000000000U; ui_test[i].expected = "17293822569102704640";
  i++; ui_test[i].num = 0x0F00000000000000U; ui_test[i].expected = "1080863910568919040";
  i++; ui_test[i].num = 0x00F0000000000000U; ui_test[i].expected = "67553994410557440";
  i++; ui_test[i].num = 0x000F000000000000U; ui_test[i].expected = "4222124650659840";
  i++; ui_test[i].num = 0x0000F00000000000U; ui_test[i].expected = "263882790666240";
  i++; ui_test[i].num = 0x00000F0000000000U; ui_test[i].expected = "16492674416640";
  i++; ui_test[i].num = 0x000000F000000000U; ui_test[i].expected = "1030792151040";
  i++; ui_test[i].num = 0x0000000F00000000U; ui_test[i].expected = "64424509440";
  i++; ui_test[i].num = 0x00000000F0000000U; ui_test[i].expected = "4026531840";
  i++; ui_test[i].num = 0x000000000F000000U; ui_test[i].expected = "251658240";
  i++; ui_test[i].num = 0x0000000000F00000U; ui_test[i].expected = "15728640";
  i++; ui_test[i].num = 0x00000000000F0000U; ui_test[i].expected = "983040";
  i++; ui_test[i].num = 0x000000000000F000U; ui_test[i].expected = "61440";
  i++; ui_test[i].num = 0x0000000000000F00U; ui_test[i].expected = "3840";
  i++; ui_test[i].num = 0x00000000000000F0U; ui_test[i].expected = "240";
  i++; ui_test[i].num = 0x000000000000000FU; ui_test[i].expected = "15";

  i++; ui_test[i].num = 0xC000000000000000U; ui_test[i].expected = "13835058055282163712";
  i++; ui_test[i].num = 0x0C00000000000000U; ui_test[i].expected = "864691128455135232";
  i++; ui_test[i].num = 0x00C0000000000000U; ui_test[i].expected = "54043195528445952";
  i++; ui_test[i].num = 0x000C000000000000U; ui_test[i].expected = "3377699720527872";
  i++; ui_test[i].num = 0x0000C00000000000U; ui_test[i].expected = "211106232532992";
  i++; ui_test[i].num = 0x00000C0000000000U; ui_test[i].expected = "13194139533312";
  i++; ui_test[i].num = 0x000000C000000000U; ui_test[i].expected = "824633720832";
  i++; ui_test[i].num = 0x0000000C00000000U; ui_test[i].expected = "51539607552";
  i++; ui_test[i].num = 0x00000000C0000000U; ui_test[i].expected = "3221225472";
  i++; ui_test[i].num = 0x000000000C000000U; ui_test[i].expected = "201326592";
  i++; ui_test[i].num = 0x0000000000C00000U; ui_test[i].expected = "12582912";
  i++; ui_test[i].num = 0x00000000000C0000U; ui_test[i].expected = "786432";
  i++; ui_test[i].num = 0x000000000000C000U; ui_test[i].expected = "49152";
  i++; ui_test[i].num = 0x0000000000000C00U; ui_test[i].expected = "3072";
  i++; ui_test[i].num = 0x00000000000000C0U; ui_test[i].expected = "192";
  i++; ui_test[i].num = 0x000000000000000CU; ui_test[i].expected = "12";

  i++; ui_test[i].num = 0x00000001U; ui_test[i].expected = "1";
  i++; ui_test[i].num = 0x00000000U; ui_test[i].expected = "0";

  num_uint_tests = i;

#endif

  for(i = 1; i <= num_uint_tests; i++) {

    for(j = 0; j<BUFSZ; j++)
      ui_test[i].result[j] = 'X';
    ui_test[i].result[BUFSZ-1] = '\0';

    (void)curl_msprintf(ui_test[i].result, "%u", ui_test[i].num);

    if(memcmp(ui_test[i].result,
               ui_test[i].expected,
               strlen(ui_test[i].expected))) {
      printf("unsigned int test #%.2d: Failed (Expected: %s Got: %s)\n",
             i, ui_test[i].expected, ui_test[i].result);
      failed++;
    }

  }

  if(!failed)
    printf("All curl_mprintf() unsigned int tests OK!\n");
  else
    printf("Some curl_mprintf() unsigned int tests Failed!\n");

  return failed;
}