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
 int /*<<< orphan*/  GLFW_RESIZABLE ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  g_window ; 
 int /*<<< orphan*/  glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowSizeCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  render ; 
 int /*<<< orphan*/  windowSizeCallback ; 

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
  g_window = glfwCreateWindow(600, 450, "GLFW resizing test - windowed", NULL, NULL);
  if (!g_window)
  {
    printf("Could not create window. Test failed.\n");      
#ifdef REPORT_RESULT
    REPORT_RESULT(0);
#endif           
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(g_window);

  // Install callbacks
  glfwSetWindowSizeCallback(g_window, windowSizeCallback);

  // Main loop
  printf("You should see a yellow canvas.\n");
  printf("Check the 'resize canvas' option on the upper right corner and then enter full screen mode.\n");
  printf("When in full screen, you should see the whole screen filled yellow, and after exiting, the yellow canvas should be restored in the window.\n");
  printf("REMARK: You MUST check the 'resize canvas' option!\n");
  emscripten_set_main_loop(render, 0, 1);

  glfwTerminate();

  return 0;
}