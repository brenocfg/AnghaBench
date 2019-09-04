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
 int /*<<< orphan*/  EDOM ; 
 int /*<<< orphan*/  EWOULDBLOCK ; 
 int errno ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strerror_r (int /*<<< orphan*/ ,char*,int) ; 

int main() {
  char* err;
  char buffer[200];

  err = strerror(EDOM);
  strerror_r(EWOULDBLOCK, buffer, 200);
  printf("<%s>\n", err);
  printf("<%s>\n", buffer);

  printf("<%d>\n", strerror_r(EWOULDBLOCK, buffer, 0));
  errno = 123;
  printf("<%d>\n", errno);

  return 0;
}