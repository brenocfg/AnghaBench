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
 int /*<<< orphan*/  emscripten_vr_cancel_display_render_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_vr_exit_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gDisplay ; 
 int /*<<< orphan*/  printf (char*) ; 
 void* renderLoopArgArg ; 
 int renderLoopArgCalled ; 

__attribute__((used)) static void renderLoopArg(void* arg) {
    emscripten_vr_cancel_display_render_loop(gDisplay);

    renderLoopArgCalled = true;
    renderLoopArgArg = arg;

    emscripten_vr_exit_present(gDisplay);

    printf("Render loop with argument was called.\n");

    return;
}