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
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  O_BINARY ; 
 int /*<<< orphan*/  PR_Cleanup () ; 
 scalar_t__ PR_Initialized () ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* libtest_arg2 ; 
 char* libtest_arg3 ; 
 int /*<<< orphan*/  memory_tracking_init () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int test (char*) ; 
 int test_argc ; 
 char** test_argv ; 

int main(int argc, char **argv)
{
  char *URL;
  int result;

#ifdef O_BINARY
#  ifdef __HIGHC__
  _setmode(stdout, O_BINARY);
#  else
  setmode(fileno(stdout), O_BINARY);
#  endif
#endif

  memory_tracking_init();

  /*
   * Setup proper locale from environment. This is needed to enable locale-
   * specific behaviour by the C library in order to test for undesired side
   * effects that could cause in libcurl.
   */
#ifdef HAVE_SETLOCALE
  setlocale(LC_ALL, "");
#endif

  if(argc< 2) {
    fprintf(stderr, "Pass URL as argument please\n");
    return 1;
  }

  test_argc = argc;
  test_argv = argv;

  if(argc>2)
    libtest_arg2 = argv[2];

  if(argc>3)
    libtest_arg3 = argv[3];

  URL = argv[1]; /* provide this to the rest */

  fprintf(stderr, "URL: %s\n", URL);

  result = test(URL);

#ifdef USE_NSS
  if(PR_Initialized())
    /* prevent valgrind from reporting possibly lost memory (fd cache, ...) */
    PR_Cleanup();
#endif

  return result;
}