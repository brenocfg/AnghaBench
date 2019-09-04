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
typedef  int ALenum ;

/* Variables and functions */
#define  AL_FORMAT_MONO16 131 
#define  AL_FORMAT_MONO8 130 
#define  AL_FORMAT_STEREO16 129 
#define  AL_FORMAT_STEREO8 128 

__attribute__((used)) static const char* alformat_string(ALenum format) {
    switch(format) {
    #define CASE(X) case X: return #X;
    CASE(AL_FORMAT_MONO8)
    CASE(AL_FORMAT_MONO16)
    CASE(AL_FORMAT_STEREO8)
    CASE(AL_FORMAT_STEREO16)
#ifdef ASSUME_AL_FLOAT32
    CASE(AL_FORMAT_MONO_FLOAT32)
    CASE(AL_FORMAT_STEREO_FLOAT32)
#endif
    #undef CASE
    }
    return "<no_string_available>";
}