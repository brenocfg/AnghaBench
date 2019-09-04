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
 int /*<<< orphan*/  GLFW_KEY_LCTRL ; 
 int /*<<< orphan*/  GLFW_MOUSE_BUTTON_1 ; 
 int GLFW_PRESS ; 
 char* GetParamName (int /*<<< orphan*/ ) ; 
 scalar_t__ glfwExtensionSupported (char const*) ; 
 int /*<<< orphan*/  glfwGetGLVersion (int*,int*,int*) ; 
 int glfwGetKey (int /*<<< orphan*/ ) ; 
 int glfwGetMouseButton (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwGetMousePos (int*,int*) ; 
 int glfwGetMouseWheel () ; 
 int glfwGetNumberOfProcessors () ; 
 void* glfwGetProcAddress (char const*) ; 
 double glfwGetTime () ; 
 int /*<<< orphan*/  glfwGetVersion (int*,int*,int*) ; 
 int glfwGetWindowParam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int*,int*) ; 
 int /*<<< orphan*/  glfwSleep (int) ; 
 unsigned int nb_params ; 
 int /*<<< orphan*/ * params ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void PullInfo(){
  printf("================================================================================\n");
  
  int major, minor, rev;
  glfwGetVersion(&major, &minor, &rev);
  printf("GLFW version is %i.%i.%i\n", major, minor, rev);
  
  int width, height;
  glfwGetWindowSize(&width, &height);
  printf("Window size is %i %i\n", width, height);
  
  int status = glfwGetKey(GLFW_KEY_LCTRL);
  if(status == GLFW_PRESS)
    printf("Left control is pressed\n");
  else
    printf("Left control is released\n");
    
  status = glfwGetMouseButton(GLFW_MOUSE_BUTTON_1);
  if(status == GLFW_PRESS)
    printf("Mouse button 1 is pressed\n");
  else
    printf("Mouse button 1 is released\n");
    
  int x, y;
  glfwGetMousePos(&x, &y);
  printf("Mouse position is %i %i\n", x, y);
  
  int wheel = glfwGetMouseWheel();
  printf("Mouse wheel pos is %i\n", wheel);
  
  double time = glfwGetTime();
  printf("Time is %f\n", time);
  
  glfwGetGLVersion(&major, &minor, &rev);
  printf("GL version is %i.%i.%i\n", major, minor, rev);
  
  int proc = glfwGetNumberOfProcessors();
  printf("%i processors are available\n", proc);
  
  unsigned int i;
  for(i = 0; i<nb_params; i++)
    printf(" - %-27s : %i\n", GetParamName(params[i]), glfwGetWindowParam(params[i]));
  
  const char* extension = "WEBGL_compressed_texture_s3tc";
  printf("'%s' extension is %s.\n", extension, glfwExtensionSupported(extension) ? "supported" : "not supported");  
  
  extension = "GL_EXT_framebuffer_object";
  printf("'%s' extension is %s.\n", extension, glfwExtensionSupported(extension) ? "supported" : "not supported");
  
  extension = "glBindBuffer";
  void* proc_addr = glfwGetProcAddress(extension);
  printf("'%s' extension proc address is %p.\n", extension, proc_addr);
  
  printf("Sleeping 1 sec...\n");
  glfwSleep(1);
  printf("...Done.\n");
  
  printf("================================================================================\n");
  
#ifdef REPORT_RESULT  
  REPORT_RESULT(1);
#endif
}