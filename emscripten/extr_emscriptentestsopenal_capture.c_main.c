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
 int EXIT_SUCCESS ; 
 float TEST_BUFFERSIZE ; 
 scalar_t__ TEST_SAMPLERATE ; 
 int /*<<< orphan*/  getchar () ; 
 int /*<<< orphan*/  ignite () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main() {

    printf(
        "This test will attempt to capture %f seconds "
        "worth of audio data from your default audio "
        "input device, and then play it back.\n"
        , TEST_BUFFERSIZE / (float) TEST_SAMPLERATE
    );
#ifdef __EMSCRIPTEN__
    printf(
        "Press the [Start Recording] button below when you're ready, then "
        "allow audio capture when asked by the browser.\n"
        "No sample should be captured until that moment.\n"
    );
    EM_ASM(
        var btn = document.createElement('input');
        btn.type = 'button';
        btn.name = btn.value = 'Start recording';
        btn.onclick = function() {
            _ignite();
            document.body.removeChild(btn);
        };
        document.body.appendChild(btn);
    );
#else
    printf("Press [Enter] when you're ready.\n");
    getchar();
    ignite();
#endif

    return EXIT_SUCCESS;
}