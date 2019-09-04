#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* capture_device_name; int format; int sample_size; int nchannels; int /*<<< orphan*/  capture_device; scalar_t__ buffer_size; scalar_t__ sample_rate; } ;
typedef  scalar_t__ ALCenum ;

/* Variables and functions */
 scalar_t__ ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER ; 
#define  AL_FORMAT_MONO16 131 
#define  AL_FORMAT_MONO8 130 
#define  AL_FORMAT_STEREO16 129 
#define  AL_FORMAT_STEREO8 128 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  alcCaptureOpenDevice (char*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  alcCaptureStart (int /*<<< orphan*/ ) ; 
 scalar_t__ alcGetError (int /*<<< orphan*/ ) ; 
 char* alcGetString (int /*<<< orphan*/ *,scalar_t__) ; 
 char* alformat_string (int) ; 
 TYPE_1__ app ; 
 int /*<<< orphan*/  end_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,unsigned int,char*,unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  iter (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void ignite() {

    app.capture_device_name = alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);

    app.capture_device = alcCaptureOpenDevice(
        app.capture_device_name, app.sample_rate, app.format, app.buffer_size
    );
    if(!app.capture_device) {
        ALCenum err = alcGetError(app.capture_device);
        fprintf(stderr, 
            "alcCaptureOpenDevice(\"%s\", sample_rate=%u, format=%s, "
            "buffer_size=%u) failed with ALC error %x (%s)\n", 
            app.capture_device_name, 
            (unsigned) app.sample_rate, alformat_string(app.format),
            (unsigned) app.buffer_size,
            (unsigned) err, alcGetString(NULL, err)
        );
        end_test(EXIT_FAILURE);
    }

    switch(app.format) {
    case AL_FORMAT_MONO8:          app.sample_size=1; app.nchannels=1; break;
    case AL_FORMAT_MONO16:         app.sample_size=2; app.nchannels=1; break;
    case AL_FORMAT_STEREO8:        app.sample_size=1; app.nchannels=2; break;
    case AL_FORMAT_STEREO16:       app.sample_size=2; app.nchannels=2; break;
#ifdef ASSUME_AL_FLOAT32
    case AL_FORMAT_MONO_FLOAT32:   app.sample_size=4; app.nchannels=1; break;
    case AL_FORMAT_STEREO_FLOAT32: app.sample_size=4; app.nchannels=2; break;
#endif
    }

    alcCaptureStart(app.capture_device);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(iter, &app, 0, 0);
#else
    for(;;) {
        iter(&app);
        usleep(16666);
    }
#endif
}