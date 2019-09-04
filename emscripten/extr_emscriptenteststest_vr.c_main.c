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
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_vr_init () ; 
 int emscripten_vr_version_major () ; 
 int emscripten_vr_version_minor () ; 
 int /*<<< orphan*/  mainloop ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char **argv) {
    if (!emscripten_vr_init()) {
        printf("Skipping: Browser does not support WebVR\n");
        return 0;
    }

    printf("Browser is running WebVR version %d.%d\n",
           emscripten_vr_version_major(),
           emscripten_vr_version_minor());

    /* 2fps -- no rAF */
    emscripten_set_main_loop(mainloop, 2, 0);
}