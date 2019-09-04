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
 char* fcvt (double,int,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,double,char*,int,int) ; 

int main() {
  int decimal, sign;
  char *buffer;
  double source = 3.1415926535;

  buffer = fcvt(source, 7, &decimal, &sign);
  printf("source: %2.10f   buffer: '%s'   decimal: %d   sign: %d\n", source,
         buffer, decimal, sign);
}