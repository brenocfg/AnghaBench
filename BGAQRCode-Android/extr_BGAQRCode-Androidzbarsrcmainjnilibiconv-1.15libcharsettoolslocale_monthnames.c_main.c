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
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  MON_1 ; 
 int /*<<< orphan*/  MON_10 ; 
 int /*<<< orphan*/  MON_11 ; 
 int /*<<< orphan*/  MON_12 ; 
 int /*<<< orphan*/  MON_2 ; 
 int /*<<< orphan*/  MON_3 ; 
 int /*<<< orphan*/  MON_4 ; 
 int /*<<< orphan*/  MON_5 ; 
 int /*<<< orphan*/  MON_6 ; 
 int /*<<< orphan*/  MON_7 ; 
 int /*<<< orphan*/  MON_8 ; 
 int /*<<< orphan*/  MON_9 ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 

int main ()
{
  setlocale(LC_ALL, "");
  printf("%s\n", nl_langinfo(MON_1));
  printf("%s\n", nl_langinfo(MON_2));
  printf("%s\n", nl_langinfo(MON_3));
  printf("%s\n", nl_langinfo(MON_4));
  printf("%s\n", nl_langinfo(MON_5));
  printf("%s\n", nl_langinfo(MON_6));
  printf("%s\n", nl_langinfo(MON_7));
  printf("%s\n", nl_langinfo(MON_8));
  printf("%s\n", nl_langinfo(MON_9));
  printf("%s\n", nl_langinfo(MON_10));
  printf("%s\n", nl_langinfo(MON_11));
  printf("%s\n", nl_langinfo(MON_12));
  exit(0);
}