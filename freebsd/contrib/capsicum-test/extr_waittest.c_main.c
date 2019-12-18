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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  WNOHANG ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int pdfork (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 scalar_t__ waitpid (int,int*,int /*<<< orphan*/ ) ; 

int main() {
  int procfd;
  int rc =  pdfork(&procfd, 0);
  if (rc < 0) {
    fprintf(stderr, "pdfork() failed rc=%d errno=%d %s\n", rc, errno, strerror(errno));
    exit(1);
  }
  if (rc == 0) { // Child process
    sleep(1);
    exit(123);
  }
  fprintf(stderr, "pdfork()ed child pid=%ld procfd=%d\n", (long)rc, procfd);
  sleep(2);  // Allow child to complete
  pid_t child = waitpid(-1, &rc, WNOHANG);
  if (child == 0) {
    fprintf(stderr, "waitpid(): no completed child found\n");
  } else if (child < 0) {
    fprintf(stderr, "waitpid(): failed errno=%d %s\n", errno, strerror(errno));
  } else {
    fprintf(stderr, "waitpid(): found completed child %ld\n", (long)child);
  }
  return 0;
}