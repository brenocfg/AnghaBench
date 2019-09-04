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
 int /*<<< orphan*/  GLFW_FSAA_SAMPLES ; 
 int /*<<< orphan*/  GLFW_WINDOW ; 
 int /*<<< orphan*/  REPORT_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINDOWS_SIZE ; 
 int /*<<< orphan*/  checkContextAttributesSupport () ; 
 int /*<<< orphan*/  draw () ; 
 int /*<<< orphan*/  glewInit () ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwOpenWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwOpenWindowHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  initGlObjects () ; 
 int /*<<< orphan*/  nbAlphaBits ; 
 int /*<<< orphan*/  nbDepthBits ; 
 int /*<<< orphan*/  nbSamples ; 
 int /*<<< orphan*/  nbStencilBits ; 
 int /*<<< orphan*/  result ; 

int main() {
  
    checkContextAttributesSupport();
  
    glfwInit();
  
#ifdef AA_ACTIVATED
    antiAliasingActivated = true;
    nbSamples = 4;
#endif
  
#ifdef DEPTH_ACTIVATED
    depthActivated = true;
    nbDepthBits = 16;
#endif  
  
#ifdef STENCIL_ACTIVATED
    stencilActivated = true;  
    nbStencilBits = 8;
#endif
  
#ifdef ALPHA_ACTIVATED
    alphaActivated = true;  
    nbAlphaBits = 8;
#endif

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, nbSamples);
    glfwOpenWindow(WINDOWS_SIZE, WINDOWS_SIZE, 8, 8, 8, nbAlphaBits, nbDepthBits, nbStencilBits, GLFW_WINDOW);
  
    glewInit();
    initGlObjects();

    draw();
  
    glfwTerminate();
  
    REPORT_RESULT(result);
  
    return 0;

}