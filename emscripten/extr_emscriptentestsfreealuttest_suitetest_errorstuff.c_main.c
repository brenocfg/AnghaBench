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
typedef  scalar_t__ ALuint ;

/* Variables and functions */
 scalar_t__ AL_NONE ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ alutCreateBufferFromFile (char*) ; 
 int /*<<< orphan*/  alutExit () ; 
 int /*<<< orphan*/  alutInit (int*,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
  ALuint buffer;

  alutInit(&argc, argv);
  buffer = alutCreateBufferFromFile("no_such_file_in_existance.wav");
  alutExit();

  if (buffer != AL_NONE)
  {
    fprintf(stderr, "expected an I/O error\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}