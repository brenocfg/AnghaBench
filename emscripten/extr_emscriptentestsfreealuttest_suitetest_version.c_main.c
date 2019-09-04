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
typedef  scalar_t__ ALboolean ;

/* Variables and functions */
 scalar_t__ AL_FALSE ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  alutExit () ; 
 int /*<<< orphan*/  alutInit (int*,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
  ALboolean ok = AL_FALSE;

  alutInit(&argc, argv);

#ifdef ALUT_API_MAJOR_VERSION
  if (alutGetMajorVersion() != ALUT_API_MAJOR_VERSION || alutGetMinorVersion() != ALUT_API_MINOR_VERSION)
  {
    fprintf(stderr,
            "WARNING: The ALUT library is version %d.%d.x but <AL/alut.h> says it's %d.%d.x!\n",
            alutGetMajorVersion(), alutGetMinorVersion(), ALUT_API_MAJOR_VERSION, ALUT_API_MINOR_VERSION);
  }
  else
  {
    fprintf(stderr, "The ALUT library is at version %d.%d.x.\n", alutGetMajorVersion(), alutGetMinorVersion());
    ok = AL_TRUE;
  }
#else
  fprintf(stderr, "WARNING: Your copy of <AL/alut.h> is pre-1.0.0,\n");
  fprintf(stderr, "but you are running the ALUT test suite from ALUT\n");
  fprintf(stderr, "version 1.0.0 or later.\n");
#endif

  alutExit();
  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}