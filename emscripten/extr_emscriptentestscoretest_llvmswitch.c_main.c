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
 int switcher (char) ; 

int main(int argc, const char *argv[]) {
  unsigned int x = 0xfffffff1;
  x >>= (argc - 1);  // force it to be unsigned for purpose of checking our
                     // switch comparison in signed/unsigned
  printf("*%d,%d,%d,%d,%d,%d*\n", switcher('a'), switcher('b'), switcher('c'),
         switcher(x), switcher(-15), switcher('e'));
  return 0;
}