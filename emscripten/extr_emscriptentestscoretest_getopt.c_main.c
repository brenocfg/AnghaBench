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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[]) {
  int flags, opt;
  int nsecs, tfnd;

  nsecs = 0;
  tfnd = 0;
  flags = 0;
  while ((opt = getopt(argc, argv, "nt:")) != -1) {
    switch (opt) {
      case 'n':
        flags = 1;
        break;
      case 't':
        nsecs = atoi(optarg);
        tfnd = 1;
        break;
      default: /* '?' */
        fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  printf("flags=%d; tfnd=%d; optind=%d\n", flags, tfnd, optind);

  if (optind >= argc) {
    fprintf(stderr, "Expected argument after options\n");
    exit(EXIT_FAILURE);
  }

  printf("name argument = %s\n", argv[optind]);

  /* Other code omitted */

  exit(EXIT_SUCCESS);
}