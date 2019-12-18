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
typedef  int /*<<< orphan*/  tmp_buf ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getawd (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* transform_dir (char*) ; 

int
main(int argc, char *argv[])
{
  char tmp_buf[MAXPATHLEN], *wd;

  if (argc == 1) {
    wd = getawd(tmp_buf, sizeof(tmp_buf));
    if (wd == NULL) {
      fprintf(stderr, "pawd: %s\n", tmp_buf);
      exit(1);
    } else {
      fprintf(stdout, "%s\n", wd);
    }
  } else {
    while (--argc) {
      wd = transform_dir(*++argv);
      fprintf(stdout, "%s\n", wd);
    }
  }
  exit(0);
}