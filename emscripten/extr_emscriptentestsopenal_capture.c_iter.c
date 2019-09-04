#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int is_playing_back; int sample_rate; size_t const nchannels; size_t const sample_size; char* capture_device_name; int /*<<< orphan*/  source; int /*<<< orphan*/  buffer; int /*<<< orphan*/  format; int /*<<< orphan*/ * context; int /*<<< orphan*/ * playback_device; int /*<<< orphan*/  capture_device; } ;
typedef  TYPE_1__ App ;
typedef  scalar_t__ ALint ;
typedef  int /*<<< orphan*/  ALCubyte ;
typedef  size_t const ALCint ;
typedef  scalar_t__ ALCenum ;
typedef  int /*<<< orphan*/  ALCboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_CAPTURE_SAMPLES ; 
 scalar_t__ ALC_NO_ERROR ; 
 int /*<<< orphan*/  AL_BUFFER ; 
 int /*<<< orphan*/  AL_SOURCE_STATE ; 
 scalar_t__ AL_STOPPED ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  alBufferData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  alDeleteBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alDeleteSources (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alGenSources (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alGetSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  alSourcePlay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcCaptureCloseDevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcCaptureSamples (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  alcCaptureStop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcCloseDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alcCreateContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alcDestroyContext (int /*<<< orphan*/ *) ; 
 scalar_t__ alcGetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcGetIntegerv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t const*) ; 
 char* alcGetString (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  alcMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alcOpenDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void iter(void *papp) {
    App* const app = papp;

    if(app->is_playing_back) {
        ALint state;
        alGetSourcei(app->source, AL_SOURCE_STATE, &state);

#ifdef __EMSCRIPTEN__
        return;
#else
        if(state != AL_STOPPED)
            return;
#endif
   
        alDeleteSources(1, &app->source);
        alDeleteBuffers(1, &app->buffer);
        alcMakeContextCurrent(NULL);
        alcDestroyContext(app->context);
        alcCloseDevice(app->playback_device); 
        end_test(EXIT_SUCCESS);
    }

    ALCint ncaptured = 0;
    alcGetIntegerv(app->capture_device, ALC_CAPTURE_SAMPLES, 1, &ncaptured);

    const ALCint WANTED_NCAPTURED = 7 * app->sample_rate;

    if(ncaptured < WANTED_NCAPTURED)
        return;

    size_t datasize = WANTED_NCAPTURED * app->nchannels * app->sample_size;

    ALCubyte *data = malloc(datasize);
    if(!data) {
        fprintf(stderr, "Out of memory!\n");
        end_test(EXIT_FAILURE);
    }

    alcCaptureSamples(app->capture_device, data, WANTED_NCAPTURED);
    ALCenum err = alcGetError(app->capture_device);
    if(err != ALC_NO_ERROR) {
        fprintf(stderr, "alcCaptureSamples() yielded an error, but wasn't supposed to! (%x, %s)\n", err, alcGetString(NULL, err));
        end_test(EXIT_FAILURE);
    }

    // This was here to see if alcCaptureSamples() would reset the number of
    // available captured samples as a side-effect.
    // Turns out, it does (on Linux with OpenAL-Soft).
    // That's important to know because this behaviour, while reasonably 
    // expected, isn't documented anywhere.
    /*
    {
        ALCint ncaptured_now = 0;
        alcGetIntegerv(app->capture_device, ALC_CAPTURE_SAMPLES, 1, &ncaptured_now);

        printf(
            "For information, number of captured sample frames :\n"
            "- Before alcCaptureSamples(): %u;\n"
            "- After  alcCaptureSamples(): %u.\n"
            , (unsigned)ncaptured, (unsigned)ncaptured_now
        );
    }
    */

    alcCaptureStop(app->capture_device);

#ifdef __EMSCRIPTEN__
    // Restarting capture must zero the reported number of captured samples.
    // Works in our case because no processing takes place until the current
    // iteration yields to the javascript main loop.
    alcCaptureStart(app->capture_device);
    alcCaptureStop(app->capture_device);
    ALCint zeroed_ncaptured = 0xdead;
    alcGetIntegerv(app->capture_device, ALC_CAPTURE_SAMPLES, 1, &zeroed_ncaptured);
    if(zeroed_ncaptured) {
        fprintf(stderr, "Restarting capture didn't zero the reported number of available sample frames!\n");
    }
#endif

    ALCboolean could_close = alcCaptureCloseDevice(app->capture_device);
    if(!could_close) {
        fprintf(stderr, "Could not close device \"%s\"!\n", app->capture_device_name);
        end_test(EXIT_FAILURE);
    }

    // We're not as careful with playback - this is already tested
    // elsewhere.
    app->playback_device = alcOpenDevice(NULL);
    assert(app->playback_device);
    app->context = alcCreateContext(app->playback_device, NULL);
    assert(app->context);
    alcMakeContextCurrent(app->context);
    alGenBuffers(1, &app->buffer);
    alGenSources(1, &app->source);
    alBufferData(app->buffer, app->format, data, datasize, app->sample_rate);
    alSourcei(app->source, AL_BUFFER, app->buffer);

    free(data);

#ifdef __EMSCRIPTEN__
    EM_ASM(
        var succeed_btn = document.createElement('input');
        var fail_btn    = document.createElement('input');
        succeed_btn.type = fail_btn.type = 'button';
        succeed_btn.name = succeed_btn.value = 'Succeed';
        fail_btn.name = fail_btn.value = 'Fail';
        succeed_btn.onclick = function() {
            //Module.ccall('end_test', null, ['number'], [0]);
            _end_test(0);
        };
        fail_btn.onclick = function() {
            //Module.ccall('end_test', null, ['number'], [1]);
            _end_test(1);
        };
        document.body.appendChild(succeed_btn);
        document.body.appendChild(fail_btn);
    );
#endif

    app->is_playing_back = true;
    alSourcePlay(app->source);
    printf(
        "You should now hear the captured audio data.\n"
#ifdef __EMSCRIPTEN__
        "Press the [Succeed] button to end the test successfully, or the [Fail] button otherwise.\n"
#endif
    );
}