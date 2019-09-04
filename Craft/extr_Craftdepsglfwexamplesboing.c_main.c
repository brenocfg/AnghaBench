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
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_DEPTH_BITS ; 
 int /*<<< orphan*/  cursor_position_callback ; 
 int /*<<< orphan*/  display () ; 
 scalar_t__ dt ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ glfwGetTime () ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetCursorPosCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMouseButtonCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetTime (double) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 scalar_t__ glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  height ; 
 int /*<<< orphan*/  init () ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  mouse_button_callback ; 
 int /*<<< orphan*/  reshape (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ t ; 
 scalar_t__ t_old ; 
 int /*<<< orphan*/  width ; 

int main( void )
{
   GLFWwindow* window;

   /* Init GLFW */
   if( !glfwInit() )
      exit( EXIT_FAILURE );

   glfwWindowHint(GLFW_DEPTH_BITS, 16);

   window = glfwCreateWindow( 400, 400, "Boing (classic Amiga demo)", NULL, NULL );
   if (!window)
   {
       glfwTerminate();
       exit( EXIT_FAILURE );
   }

   glfwSetFramebufferSizeCallback(window, reshape);
   glfwSetKeyCallback(window, key_callback);
   glfwSetMouseButtonCallback(window, mouse_button_callback);
   glfwSetCursorPosCallback(window, cursor_position_callback);

   glfwMakeContextCurrent(window);
   glfwSwapInterval( 1 );

   glfwGetFramebufferSize(window, &width, &height);
   reshape(window, width, height);

   glfwSetTime( 0.0 );

   init();

   /* Main loop */
   for (;;)
   {
       /* Timing */
       t = glfwGetTime();
       dt = t - t_old;
       t_old = t;

       /* Draw one frame */
       display();

       /* Swap buffers */
       glfwSwapBuffers(window);
       glfwPollEvents();

       /* Check if we are still running */
       if (glfwWindowShouldClose(window))
           break;
   }

   glfwTerminate();
   exit( EXIT_SUCCESS );
}