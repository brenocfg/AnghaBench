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

/* Variables and functions */
 int /*<<< orphan*/  AL_BUFFER ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  alGenSources (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alSourcePlay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alutCreateBufferHelloWorld () ; 
 int /*<<< orphan*/  alutExit () ; 
 int /*<<< orphan*/  alutInit (int*,char**) ; 
 int /*<<< orphan*/  alutSleep (int) ; 

int main(int argc, char **argv)
{
  ALuint helloBuffer, helloSource;

  alutInit(&argc, argv);
  helloBuffer = alutCreateBufferHelloWorld();
  alGenSources(1, &helloSource);
  alSourcei(helloSource, AL_BUFFER, helloBuffer);
  alSourcePlay(helloSource);
  alutSleep(1);
  alutExit();
  return EXIT_SUCCESS;
}