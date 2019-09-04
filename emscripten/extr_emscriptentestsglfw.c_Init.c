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
 int /*<<< orphan*/  GLFW_KEY_REPEAT ; 
 int /*<<< orphan*/  GLFW_RED_BITS ; 
 int /*<<< orphan*/  GLFW_WINDOW ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 scalar_t__ GL_TRUE ; 
 int /*<<< orphan*/  OnCharPressed ; 
 int /*<<< orphan*/  OnClose ; 
 int /*<<< orphan*/  OnKeyPressed ; 
 int /*<<< orphan*/  OnMouseClick ; 
 int /*<<< orphan*/  OnMouseMove ; 
 int /*<<< orphan*/  OnMouseWheel ; 
 int /*<<< orphan*/  OnRefresh ; 
 int /*<<< orphan*/  OnResize ; 
 int /*<<< orphan*/  PullInfo () ; 
 int /*<<< orphan*/  Shut_Down (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  glFrustum (double,double,double,double,int,int) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwEnable (int /*<<< orphan*/ ) ; 
 int glfwGetWindowParam (int /*<<< orphan*/ ) ; 
 scalar_t__ glfwInit () ; 
 scalar_t__ glfwOpenWindow (int const,int const,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwOpenWindowHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glfwSetCharCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMouseButtonCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMousePosCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMouseWheelCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowCloseCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowRefreshCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowSizeCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowTitle (char*) ; 
 int /*<<< orphan*/  on_resize_called ; 

void Init()
{
  const int window_width = 800,
           window_height = 600;
 
  if (glfwInit() != GL_TRUE)
    Shut_Down(1);

  glfwEnable(GLFW_KEY_REPEAT); // test for issue #3059

  int red_bits = glfwGetWindowParam(GLFW_RED_BITS);
  glfwOpenWindowHint(GLFW_RED_BITS, 8);
  assert(glfwGetWindowParam(GLFW_RED_BITS) == 8);
  glfwOpenWindowHint(GLFW_RED_BITS, red_bits);

  // 800 x 600, 16 bit color, no depth, alpha or stencil buffers, windowed
  if (glfwOpenWindow(window_width, window_height, 5, 6, 5,
                  0, 0, 0, GLFW_WINDOW) != GL_TRUE)
    Shut_Down(1);
  glfwSetWindowTitle("The GLFW Window");
 
  glfwSetKeyCallback(OnKeyPressed);
  glfwSetCharCallback(OnCharPressed);
  glfwSetWindowCloseCallback(OnClose);
  glfwSetWindowSizeCallback(OnResize);
  if (!on_resize_called)
  {
    Shut_Down(1);
  }

  glfwSetWindowRefreshCallback(OnRefresh);
  glfwSetMouseWheelCallback(OnMouseWheel);
  glfwSetMousePosCallback(OnMouseMove);
  glfwSetMouseButtonCallback(OnMouseClick);
  
  // set the projection matrix to a normal frustum with a max depth of 50
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect_ratio = ((float)window_height) / window_width;
  glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
  glMatrixMode(GL_MODELVIEW);
  
  PullInfo();
}