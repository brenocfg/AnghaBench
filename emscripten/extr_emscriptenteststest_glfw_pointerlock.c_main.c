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
 int /*<<< orphan*/  GLFW_CURSOR ; 
 int /*<<< orphan*/  GLFW_CURSOR_DISABLED ; 
 int /*<<< orphan*/  GLFW_RESIZABLE ; 
 int /*<<< orphan*/  OnMouseClick ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  g_window ; 
 int /*<<< orphan*/  glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetInputMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMouseButtonCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  render ; 

int main() {
  // Setup g_window
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
  {
    printf("Could not create window. Test failed.\n");      
#ifdef REPORT_RESULT
    REPORT_RESULT(0);
#endif
    return -1;
  }
  glfwWindowHint(GLFW_RESIZABLE , 1);
  g_window = glfwCreateWindow(600, 450, "GLFW pointerlock test", NULL, NULL);
  if (!g_window)
  {
    printf("Could not create window. Test failed.\n");      
#ifdef REPORT_RESULT
    REPORT_RESULT(result);
#endif
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(g_window);

  // Try to disable cursor by entering pointer lock. If pointer lock failed (because glfwSetInputMode wasn't called in a user event),
  // then clicking the canvas should also try to lock the pointer, as long as the cursor mode is GLFW_CURSOR_DISABLED.
  glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // When we see enough clicks, we close the window
  glfwSetMouseButtonCallback(g_window, OnMouseClick);

  // Main loop
  printf("Click the canvas to enter pointer lock mode. The browser should offer to hide the mouse pointer. Make sure to accept it.\n");
  printf("If you exit pointer lock (such as pressing ESC on keyboard), clicking the canvas should lock the pointer again.\n");
  emscripten_set_main_loop(render, 0, 1);

  glfwTerminate();

  return 0;
}