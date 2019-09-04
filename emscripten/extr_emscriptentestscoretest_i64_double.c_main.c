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
 int JSDOUBLE_IS_NEGZERO (int) ; 
 int JSINT64_IS_NEGZERO (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

int main(int argc, char* argv[]) {
  printf("*%d,%d,%d,%d*\n", JSDOUBLE_IS_NEGZERO(0), JSDOUBLE_IS_NEGZERO(-0),
         JSDOUBLE_IS_NEGZERO(-1), JSDOUBLE_IS_NEGZERO(+1));
  printf("*%d,%d,%d,%d*\n", JSINT64_IS_NEGZERO(0), JSINT64_IS_NEGZERO(-0),
         JSINT64_IS_NEGZERO(-1), JSINT64_IS_NEGZERO(+1));
  return 0;
}