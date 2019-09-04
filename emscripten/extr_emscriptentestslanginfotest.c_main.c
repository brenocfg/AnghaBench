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
 int ABDAY_1 ; 
 int ABDAY_2 ; 
 int ABDAY_3 ; 
 int ABDAY_4 ; 
 int ABDAY_5 ; 
 int ABDAY_6 ; 
 int ABDAY_7 ; 
 int ABMON_1 ; 
 int ABMON_10 ; 
 int ABMON_11 ; 
 int ABMON_12 ; 
 int ABMON_2 ; 
 int ABMON_3 ; 
 int ABMON_4 ; 
 int ABMON_5 ; 
 int ABMON_6 ; 
 int ABMON_7 ; 
 int ABMON_8 ; 
 int ABMON_9 ; 
 int ALT_DIGITS ; 
 int AM_STR ; 
 int CODESET ; 
 int CRNCYSTR ; 
 int DAY_1 ; 
 int DAY_2 ; 
 int DAY_3 ; 
 int DAY_4 ; 
 int DAY_5 ; 
 int DAY_6 ; 
 int DAY_7 ; 
 int D_FMT ; 
 int D_T_FMT ; 
 int ERA ; 
 int ERA_D_FMT ; 
 int ERA_D_T_FMT ; 
 int ERA_T_FMT ; 
 int MON_1 ; 
 int MON_10 ; 
 int MON_11 ; 
 int MON_12 ; 
 int MON_2 ; 
 int MON_3 ; 
 int MON_4 ; 
 int MON_5 ; 
 int MON_6 ; 
 int MON_7 ; 
 int MON_8 ; 
 int MON_9 ; 
 int NOEXPR ; 
 int PM_STR ; 
 int RADIXCHAR ; 
 int THOUSEP ; 
 int T_FMT ; 
 int T_FMT_AMPM ; 
 int YESEXPR ; 
 char* nl_langinfo (int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

int main() {
  printf("%16s: \"%s\"\n", "CODESET", nl_langinfo(CODESET));
  printf("%16s: \"%s\"\n", "D_T_FMT", nl_langinfo(D_T_FMT));
  printf("%16s: \"%s\"\n", "D_FMT", nl_langinfo(D_FMT));
  printf("%16s: \"%s\"\n", "T_FMT", nl_langinfo(T_FMT));
  printf("%16s: \"%s\"\n", "T_FMT_AMPM", nl_langinfo(T_FMT_AMPM));
  printf("%16s: \"%s\"\n", "AM_STR", nl_langinfo(AM_STR));
  printf("%16s: \"%s\"\n", "PM_STR", nl_langinfo(PM_STR));
  printf("%16s: \"%s\"\n", "DAY_1", nl_langinfo(DAY_1));
  printf("%16s: \"%s\"\n", "DAY_2", nl_langinfo(DAY_2));
  printf("%16s: \"%s\"\n", "DAY_3", nl_langinfo(DAY_3));
  printf("%16s: \"%s\"\n", "DAY_4", nl_langinfo(DAY_4));
  printf("%16s: \"%s\"\n", "DAY_5", nl_langinfo(DAY_5));
  printf("%16s: \"%s\"\n", "DAY_6", nl_langinfo(DAY_6));
  printf("%16s: \"%s\"\n", "DAY_7", nl_langinfo(DAY_7));
  printf("%16s: \"%s\"\n", "ABDAY_1", nl_langinfo(ABDAY_1));
  printf("%16s: \"%s\"\n", "ABDAY_2", nl_langinfo(ABDAY_2));
  printf("%16s: \"%s\"\n", "ABDAY_3", nl_langinfo(ABDAY_3));
  printf("%16s: \"%s\"\n", "ABDAY_4", nl_langinfo(ABDAY_4));
  printf("%16s: \"%s\"\n", "ABDAY_5", nl_langinfo(ABDAY_5));
  printf("%16s: \"%s\"\n", "ABDAY_6", nl_langinfo(ABDAY_6));
  printf("%16s: \"%s\"\n", "ABDAY_7", nl_langinfo(ABDAY_7));
  printf("%16s: \"%s\"\n", "MON_1", nl_langinfo(MON_1));
  printf("%16s: \"%s\"\n", "MON_2", nl_langinfo(MON_2));
  printf("%16s: \"%s\"\n", "MON_3", nl_langinfo(MON_3));
  printf("%16s: \"%s\"\n", "MON_4", nl_langinfo(MON_4));
  printf("%16s: \"%s\"\n", "MON_5", nl_langinfo(MON_5));
  printf("%16s: \"%s\"\n", "MON_6", nl_langinfo(MON_6));
  printf("%16s: \"%s\"\n", "MON_7", nl_langinfo(MON_7));
  printf("%16s: \"%s\"\n", "MON_8", nl_langinfo(MON_8));
  printf("%16s: \"%s\"\n", "MON_9", nl_langinfo(MON_9));
  printf("%16s: \"%s\"\n", "MON_10", nl_langinfo(MON_10));
  printf("%16s: \"%s\"\n", "MON_11", nl_langinfo(MON_11));
  printf("%16s: \"%s\"\n", "MON_12", nl_langinfo(MON_12));
  printf("%16s: \"%s\"\n", "ABMON_1", nl_langinfo(ABMON_1));
  printf("%16s: \"%s\"\n", "ABMON_2", nl_langinfo(ABMON_2));
  printf("%16s: \"%s\"\n", "ABMON_3", nl_langinfo(ABMON_3));
  printf("%16s: \"%s\"\n", "ABMON_4", nl_langinfo(ABMON_4));
  printf("%16s: \"%s\"\n", "ABMON_5", nl_langinfo(ABMON_5));
  printf("%16s: \"%s\"\n", "ABMON_6", nl_langinfo(ABMON_6));
  printf("%16s: \"%s\"\n", "ABMON_7", nl_langinfo(ABMON_7));
  printf("%16s: \"%s\"\n", "ABMON_8", nl_langinfo(ABMON_8));
  printf("%16s: \"%s\"\n", "ABMON_9", nl_langinfo(ABMON_9));
  printf("%16s: \"%s\"\n", "ABMON_10", nl_langinfo(ABMON_10));
  printf("%16s: \"%s\"\n", "ABMON_11", nl_langinfo(ABMON_11));
  printf("%16s: \"%s\"\n", "ABMON_12", nl_langinfo(ABMON_12));
  printf("%16s: \"%s\"\n", "ERA", nl_langinfo(ERA));
  printf("%16s: \"%s\"\n", "ERA_D_FMT", nl_langinfo(ERA_D_FMT));
  printf("%16s: \"%s\"\n", "ERA_D_T_FMT", nl_langinfo(ERA_D_T_FMT));
  printf("%16s: \"%s\"\n", "ERA_T_FMT", nl_langinfo(ERA_T_FMT));
  printf("%16s: \"%s\"\n", "ALT_DIGITS", nl_langinfo(ALT_DIGITS));
  printf("%16s: \"%s\"\n", "RADIXCHAR", nl_langinfo(RADIXCHAR));
  printf("%16s: \"%s\"\n", "THOUSEP", nl_langinfo(THOUSEP));
  printf("%16s: \"%s\"\n", "YESEXPR", nl_langinfo(YESEXPR));
  printf("%16s: \"%s\"\n", "NOEXPR", nl_langinfo(NOEXPR));
  printf("%16s: \"%s\"\n", "CRNCYSTR", nl_langinfo(CRNCYSTR));

  printf("%16s: \"%s\"\n", "(bad value)", nl_langinfo(123));

  return 0;
}