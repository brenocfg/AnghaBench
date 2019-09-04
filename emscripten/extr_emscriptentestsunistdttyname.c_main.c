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
 int ERANGE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 char* ctermid (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strstr (char*,char*) ; 
 char* ttyname (int) ; 
 int ttyname_r (int,char*,int) ; 

int main() {
  int err;
  int stdin, null, dev;
  char buffer[256];
  char* result;

  stdin = open("/dev/stdin", O_RDONLY);
  null = open("/dev/null", O_RDONLY);
  dev = open("/dev", O_RDONLY);

  result = ctermid(buffer);
  assert(!strcmp(result, "/dev/tty"));

  // strstr instead of strcmp as native code may
  // be using a virtual console (e.g. /dev/tty02)
  err = ttyname_r(stdin, buffer, 256);
  assert(!err);
  assert(strstr(buffer, "/dev/tty"));

  err = ttyname_r(stdin, buffer, 2);
  assert(err == ERANGE);

  result = ttyname(stdin);
  assert(strstr(result, "/dev/tty"));

  result = ttyname(null);
  assert(!result);

  result = ttyname(dev);
  assert(!result);

  puts("success");

  return EXIT_SUCCESS;
}