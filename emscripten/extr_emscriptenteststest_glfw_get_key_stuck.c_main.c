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
 int /*<<< orphan*/  glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  render () ; 
 int step ; 
 int /*<<< orphan*/  window ; 

int main() {
    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "test_glfw_get_key_stuck", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    printf("%d. Press and hold spacebar\n", step);

#ifdef __EMSCRIPTEN__
    emscripten_set_blur_callback(NULL, NULL, EM_TRUE, on_focuspocus);
    emscripten_set_focus_callback(NULL, NULL, EM_TRUE, on_focuspocus);
    emscripten_set_focusin_callback(NULL, NULL, EM_TRUE, on_focuspocus);
    emscripten_set_focusout_callback(NULL, NULL, EM_TRUE, on_focuspocus);

    emscripten_set_main_loop(render, 0, 1);
#else
    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
#endif

    glfwTerminate();
    return 0;
}