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
struct adpcm_state {int sample; int index; } ;

/* Variables and functions */
 scalar_t__* indexTable ; 
 int* stepsizeTable ; 

void S_AdpcmDecode( const char indata[], short *outdata, int len, struct adpcm_state *state ) {
    signed char *inp;		/* Input buffer pointer */
    int outp;			/* output buffer pointer */
    int sign;			/* Current adpcm sign bit */
    int delta;			/* Current adpcm output value */
    int step;			/* Stepsize */
    int valpred;		/* Predicted value */
    int vpdiff;			/* Current change to valpred */
    int index;			/* Current step change index */
    int inputbuffer;		/* place to keep next 4-bit value */
    int bufferstep;		/* toggle between inputbuffer/input */

    outp = 0;
    inp = (signed char *)indata;

    valpred = state->sample;
    index = state->index;
    step = stepsizeTable[index];

    bufferstep = 0;
    inputbuffer = 0;	// quiet a compiler warning
    for ( ; len > 0 ; len-- ) {
		
		/* Step 1 - get the delta value */
		if ( bufferstep ) {
			delta = inputbuffer & 0xf;
		} else {
			inputbuffer = *inp++;
			delta = (inputbuffer >> 4) & 0xf;
		}
		bufferstep = !bufferstep;

		/* Step 2 - Find new index value (for later) */
		index += indexTable[delta];
		if ( index < 0 ) index = 0;
		if ( index > 88 ) index = 88;

		/* Step 3 - Separate sign and magnitude */
		sign = delta & 8;
		delta = delta & 7;

		/* Step 4 - Compute difference and new predicted value */
		/*
		** Computes 'vpdiff = (delta+0.5)*step/4', but see comment
		** in adpcm_coder.
		*/
		vpdiff = step >> 3;
		if ( delta & 4 ) vpdiff += step;
		if ( delta & 2 ) vpdiff += step>>1;
		if ( delta & 1 ) vpdiff += step>>2;

		if ( sign )
		  valpred -= vpdiff;
		else
		  valpred += vpdiff;

		/* Step 5 - clamp output value */
		if ( valpred > 32767 )
		  valpred = 32767;
		else if ( valpred < -32768 )
		  valpred = -32768;

		/* Step 6 - Update step value */
		step = stepsizeTable[index];

		/* Step 7 - Output value */
		outdata[outp] = valpred;
		outp++;
    }

    state->sample = valpred;
    state->index = index;
}