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
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int sun2amd_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sun2amd_open (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sun2amd_usage () ; 

int
main(int argc, char **argv)
{
  /* default in/out to stdin/stdout */
  FILE *sun_in = stdin, *amd_out = stdout;
  int opt, retval = 1;

  while ((opt = getopt(argc, argv , "i:o:hH")) != -1) {
    switch (opt) {

    case 'i':
      if ((sun_in = sun2amd_open(optarg,"r")) == NULL) {
	goto err;
      }
      break;

    case 'o':
      if ((amd_out = sun2amd_open(optarg,"w")) == NULL) {
	goto err;
      }
      break;

    case 'h':
    case 'H':
      sun2amd_usage();
      goto err;
    }
  }

  retval = sun2amd_convert(sun_in,amd_out);

 err:
  exit(retval);
}