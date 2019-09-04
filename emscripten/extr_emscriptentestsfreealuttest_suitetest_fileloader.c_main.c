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
typedef  int /*<<< orphan*/  ALenum ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  alutExit () ; 
 int /*<<< orphan*/  alutGetError () ; 
 char* alutGetErrorString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alutInit (int*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  playFile (char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
  /* Initialise ALUT and eat any ALUT-specific commandline flags. */
  if (!alutInit(&argc, argv))
  {
    ALenum error = alutGetError();

    fprintf(stderr, "%s\n", alutGetErrorString(error));
    exit(EXIT_FAILURE);
  }

  /* If everything is OK, play the sound files and exit when finished. */
  playFile("file1.wav");
  playFile("file2.au");
  playFile("file3.raw");

  if (!alutExit())
  {
    ALenum error = alutGetError();

    fprintf(stderr, "%s\n", alutGetErrorString(error));
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}