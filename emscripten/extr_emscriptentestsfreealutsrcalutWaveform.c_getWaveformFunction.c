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
typedef  int /*<<< orphan*/ * waveformFunction ;
typedef  int ALenum ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_INVALID_ENUM ; 
#define  ALUT_WAVEFORM_IMPULSE 132 
#define  ALUT_WAVEFORM_SAWTOOTH 131 
#define  ALUT_WAVEFORM_SINE 130 
#define  ALUT_WAVEFORM_SQUARE 129 
#define  ALUT_WAVEFORM_WHITENOISE 128 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveformImpulse ; 
 int /*<<< orphan*/  waveformSawtooth ; 
 int /*<<< orphan*/  waveformSine ; 
 int /*<<< orphan*/  waveformSquare ; 
 int /*<<< orphan*/  waveformWhitenoise ; 

__attribute__((used)) static waveformFunction getWaveformFunction(ALenum waveshape)
{
  switch (waveshape)
  {
  case ALUT_WAVEFORM_SINE:
    return &waveformSine;
  case ALUT_WAVEFORM_SQUARE:
    return &waveformSquare;
  case ALUT_WAVEFORM_SAWTOOTH:
    return &waveformSawtooth;
  case ALUT_WAVEFORM_WHITENOISE:
    return &waveformWhitenoise;
  case ALUT_WAVEFORM_IMPULSE:
    return &waveformImpulse;
  }
  _alutSetError(ALUT_ERROR_INVALID_ENUM);
  return NULL;
}