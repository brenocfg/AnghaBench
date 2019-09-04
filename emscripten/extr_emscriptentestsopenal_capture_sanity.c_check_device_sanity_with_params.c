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
typedef  scalar_t__ ALCuint ;
typedef  scalar_t__ ALCsizei ;
typedef  scalar_t__ ALCenum ;
typedef  int /*<<< orphan*/  ALCdevice ;
typedef  int /*<<< orphan*/  ALCboolean ;

/* Variables and functions */
 scalar_t__ ALC_CAPTURE_DEVICE_SPECIFIER ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  alcCaptureCloseDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alcCaptureOpenDevice (char const*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ alcGetError (int /*<<< orphan*/ *) ; 
 char* alcGetString (int /*<<< orphan*/ *,scalar_t__) ; 
 char* alformat_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  printf (char*,char const*,unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  result ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void check_device_sanity_with_params(const char *name, ALCuint sample_rate, ALenum format, ALCsizei buffer_size) {

    printf(
        "Testing \"%s\" @%uHz with %u sample-frames (format: %s)...\n", 
        name, (unsigned)sample_rate, (unsigned) buffer_size,
        alformat_string(format)
    );

    ALCdevice* dev = alcCaptureOpenDevice(name, sample_rate, format, buffer_size);

    if(dev) {
        const char *claimed = alcGetString(dev, ALC_CAPTURE_DEVICE_SPECIFIER);
        if(strcmp(name, claimed)) {
            fprintf(stderr, "The device \"%s\" claims to be actually named \"%s\", which is not correct behavior.\n", name, claimed);
            result = EXIT_FAILURE;
        }
        ALCboolean could_close = alcCaptureCloseDevice(dev);
        if(!could_close) {
            fprintf(stderr, "alcCaptureCloseDevice() with \"%s\" failed!\n", name);
            result = EXIT_FAILURE;
        }
        return;
    }

    ALCenum err = alcGetError(dev);
    fprintf(stderr,
        "alcCaptureOpenDevice(\"%s\", sample_rate=%u, format=%s, "
        "buffer_size=%u) failed with ALC error %x (%s)\n", 
        name, (unsigned)sample_rate, alformat_string(format), 
        (unsigned) buffer_size,
        (unsigned) err, alcGetString(NULL, err)
    );
    result = EXIT_FAILURE;
}