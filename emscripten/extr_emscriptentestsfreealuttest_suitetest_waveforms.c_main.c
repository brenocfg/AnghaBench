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
 int /*<<< orphan*/  ALUT_WAVEFORM_IMPULSE ; 
 int /*<<< orphan*/  ALUT_WAVEFORM_SAWTOOTH ; 
 int /*<<< orphan*/  ALUT_WAVEFORM_SINE ; 
 int /*<<< orphan*/  ALUT_WAVEFORM_SQUARE ; 
 int /*<<< orphan*/  ALUT_WAVEFORM_WHITENOISE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  alutExit () ; 
 int /*<<< orphan*/  alutInit (int*,char**) ; 
 int /*<<< orphan*/  playTone (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
  alutInit(&argc, argv);

  playTone(ALUT_WAVEFORM_SINE);
  playTone(ALUT_WAVEFORM_SQUARE);
  playTone(ALUT_WAVEFORM_SAWTOOTH);
  playTone(ALUT_WAVEFORM_WHITENOISE);
  playTone(ALUT_WAVEFORM_IMPULSE);

  alutExit();
  return EXIT_SUCCESS;
}