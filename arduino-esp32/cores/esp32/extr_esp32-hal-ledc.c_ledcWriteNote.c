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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  size_t note_t ;

/* Variables and functions */
 size_t NOTE_MAX ; 
 double ledcWriteTone (int,double) ; 

double ledcWriteNote(uint8_t chan, note_t note, uint8_t octave){
    const uint16_t noteFrequencyBase[12] = {
    //   C        C#       D        Eb       E        F       F#        G       G#        A       Bb        B
        4186,    4435,    4699,    4978,    5274,    5588,    5920,    6272,    6645,    7040,    7459,    7902
    };

    if(octave > 8 || note >= NOTE_MAX){
        return 0;
    }
    double noteFreq =  (double)noteFrequencyBase[note] / (double)(1 << (8-octave));
    return ledcWriteTone(chan, noteFreq);
}