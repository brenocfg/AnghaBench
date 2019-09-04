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
 int /*<<< orphan*/  Mix_CloseAudio () ; 
 int /*<<< orphan*/  Mix_FreeChunk (int /*<<< orphan*/ ) ; 
 scalar_t__ Mix_Playing (int) ; 
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/  emscripten_cancel_main_loop () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  wave ; 

void sound_loop_then_quit() {
    if (Mix_Playing(-1))
        return;
    printf("Done audio\n");
    Mix_FreeChunk(wave);
    Mix_CloseAudio();

    emscripten_cancel_main_loop();
    printf("Shutting down\n");
    REPORT_RESULT(1);
}