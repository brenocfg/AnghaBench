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
typedef  scalar_t__ ALint ;
typedef  scalar_t__ ALenum ;

/* Variables and functions */
 scalar_t__ ALUT_ERROR_NO_ERROR ; 
 int /*<<< orphan*/  AL_BUFFER ; 
 scalar_t__ AL_NONE ; 
 scalar_t__ AL_PLAYING ; 
 int /*<<< orphan*/  AL_SOURCE_STATE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  alGenSources (int,scalar_t__*) ; 
 scalar_t__ alGetError () ; 
 int /*<<< orphan*/  alGetSourcei (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 char* alGetString (scalar_t__) ; 
 int /*<<< orphan*/  alSourcePlay (scalar_t__) ; 
 int /*<<< orphan*/  alSourcei (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ alutCreateBufferFromFile (char const*) ; 
 int /*<<< orphan*/  alutExit () ; 
 scalar_t__ alutGetError () ; 
 char* alutGetErrorString (scalar_t__) ; 
 int /*<<< orphan*/  alutSleep (float) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void playFile(const char *fileName)
{
  ALuint buffer;
  ALuint source;
  ALenum error;
  ALint status;

  /* Create an AL buffer from the given sound file. */
  buffer = alutCreateBufferFromFile(fileName);
  if (buffer == AL_NONE)
  {
    error = alutGetError();
    fprintf(stderr, "Error loading file: '%s'\n", alutGetErrorString(error));
    alutExit();
    exit(EXIT_FAILURE);
  }

  /* Generate a single source, attach the buffer to it and start playing. */
  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, buffer);
  alSourcePlay(source);

  /* Normally nothing should go wrong above, but one never knows... */
  error = alGetError();
  if (error != ALUT_ERROR_NO_ERROR)
  {
    fprintf(stderr, "%s\n", alGetString(error));
    alutExit();
    exit(EXIT_FAILURE);
  }

  /* Check every 0.1 seconds if the sound is still playing. */
  do
  {
    alutSleep(0.1f);
    alGetSourcei(source, AL_SOURCE_STATE, &status);
  }
  while (status == AL_PLAYING);
}