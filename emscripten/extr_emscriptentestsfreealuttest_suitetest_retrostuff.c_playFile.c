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
typedef  int /*<<< orphan*/  ALuint ;
typedef  int /*<<< orphan*/  ALsizei ;
typedef  scalar_t__ ALint ;
typedef  scalar_t__ ALenum ;
typedef  int /*<<< orphan*/  ALbyte ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 scalar_t__ ALUT_ERROR_NO_ERROR ; 
 int /*<<< orphan*/  AL_BUFFER ; 
 scalar_t__ AL_PLAYING ; 
 int /*<<< orphan*/  AL_SOURCE_STATE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  alBufferData (int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alGenSources (int,int /*<<< orphan*/ *) ; 
 scalar_t__ alGetError () ; 
 int /*<<< orphan*/  alGetSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 char* alGetString (scalar_t__) ; 
 int /*<<< orphan*/  alSourcePlay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alutExit () ; 
 int /*<<< orphan*/  alutLoadWAVFile (int /*<<< orphan*/ *,scalar_t__*,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alutSleep (float) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void playFile(const char *fileName)
{
  ALenum format;
  void *data;
  ALsizei size;
  ALsizei frequency;

#if !defined(__APPLE__)
  ALboolean loop;
#endif
  ALuint buffer;
  ALuint source;
  ALenum error;
  ALint status;

  /* Create an AL buffer from the given sound file. */
  alutLoadWAVFile((ALbyte *) "file1.wav", &format, &data, &size, &frequency
#if !defined(__APPLE__)
                  , &loop
#endif
    );
  alGenBuffers(1, &buffer);
  alBufferData(buffer, format, data, size, frequency);
  free(data);

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