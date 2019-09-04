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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  putchar (int) ; 

int main() {
  FILE *fp;
  int c;

  malloc(20000000);  // Enlarge memory

  fp = fopen("test.txt", "r");
  int nChars = 0;
  while ((c = fgetc(fp)) != EOF)
  {
    putchar(c);
    ++nChars;
  }
#ifdef REPORT_RESULT
  REPORT_RESULT(nChars);
#endif
}