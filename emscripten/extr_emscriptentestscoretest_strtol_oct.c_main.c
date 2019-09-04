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
 long strtol (char const*,char**,int) ; 

int main() {
  const char *STRING = "0 -035 +04711";
  char *end_char;

  // undefined base
  long l1 = strtol(STRING, &end_char, 0);
  long l2 = strtol(end_char, &end_char, 0);
  long l3 = strtol(end_char, NULL, 0);

  // defined base
  long l4 = strtol(STRING, &end_char, 8);
  long l5 = strtol(end_char, &end_char, 8);
  long l6 = strtol(end_char, NULL, 8);

  printf("%d%d%d%d%d%d\n", l1 == 0, l2 == -29, l3 == 2505, l4 == 0, l5 == -29,
         l6 == 2505);
  return 0;
}