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
 scalar_t__ EAGAIN ; 
 int EOF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 int ferror (int /*<<< orphan*/ ) ; 
 int fgetc (int /*<<< orphan*/ ) ; 
 scalar_t__ line ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int scanf (char*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

void main_loop()
{
  char str[10] = {0};
  int ret;

  errno = 0;
  while (errno != EAGAIN) {
    if (line == 0) {
      ret = fgetc(stdin);
      if (ret != EOF) putc(ret, stdout);
      if (ret == '\n') line++;
    } else if (line > 0) {
      ret = scanf("%10s", str);
      if (ret > 0) puts(str);
    }

    int err = ferror(stdin);
    if (ferror(stdin) && errno != EAGAIN) {
      printf("error %d\n", err);
      exit(EXIT_FAILURE);
    }

    if (feof(stdin)) {
      puts("eof");
      exit(EXIT_SUCCESS);
    }

    clearerr(stdin);
  }
}