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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_WINDOW ; 
 scalar_t__ GL_TRUE ; 
 scalar_t__ glfwInit () ; 
 scalar_t__ glfwOpenWindow (int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  printf (char*) ; 

int main() {
    printf("main function started\n");
    if (glfwInit() != GL_TRUE) {
        printf("glfwInit() failed\n");
        glfwTerminate();
    } else {
        printf("glfwInit() success\n");
        if (glfwOpenWindow(640, 480, 8, 8, 8, 8, 16, 0, GLFW_WINDOW) != GL_TRUE){
            printf("glfwOpenWindow() failed\n");
            glfwTerminate();
        } else {
          printf("glfwOpenWindow() success\n");
        }
    }
#ifdef REPORT_RESULT  
    REPORT_RESULT(1);
#endif
    return EXIT_SUCCESS;
}