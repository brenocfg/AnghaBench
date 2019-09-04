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
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 
 long long strtoll (char const*,char**,int) ; 

int main() {
  const char *STRING = "4 -38 +4711";
  char *end_char;

  // undefined base
  long long int l1 = strtoll(STRING, &end_char, 0);
  long long int l2 = strtoll(end_char, &end_char, 0);
  long long int l3 = strtoll(end_char, NULL, 0);

  // defined base
  long long int l4 = strtoll(STRING, &end_char, 10);
  long long int l5 = strtoll(end_char, &end_char, 10);
  long long int l6 = strtoll(end_char, NULL, 10);

  printf("%d%d%d%d%d%d\n", l1 == 4, l2 == -38, l3 == 4711, l4 == 4, l5 == -38,
         l6 == 4711);
  return 0;
}