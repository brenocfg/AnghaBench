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
 scalar_t__ EBADF ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int isatty (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 

int main() {
  int err;

  err = isatty(-1);
  assert(!err);
  assert(errno == EBADF);

  err = isatty(open("/dev/stdin", O_RDONLY));
  assert(err == 1);

  err = isatty(open("/dev/null", O_RDONLY));
  assert(!err);

  err = isatty(open("/dev", O_RDONLY));
  assert(!err);

  puts("success");

  return EXIT_SUCCESS;
}