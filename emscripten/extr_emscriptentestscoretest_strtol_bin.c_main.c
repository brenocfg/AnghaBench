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
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 long strtol (char const*,char**,int) ; 

int main() {
  const char *STRING = "1 -101 +1011";
  char *end_char;

  // defined base
  long l4 = strtol(STRING, &end_char, 2);
  long l5 = strtol(end_char, &end_char, 2);
  long l6 = strtol(end_char, NULL, 2);

  printf("%d%d%d\n", l4 == 1, l5 == -5, l6 == 11);
  return 0;
}