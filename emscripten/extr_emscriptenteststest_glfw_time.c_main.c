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
 float glfwGetTime () ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwSetTime (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int result ; 

int main() {
    if (!glfwInit()) {
        return -1;
    }

    float t = glfwGetTime();
    printf("glfwGetTime() = %f\n", t);

    printf("glfwSetTime(50)\n");
    glfwSetTime(50);

    // Expect time to be slightly greater than what we set
    t = glfwGetTime();
    printf("glfwGetTime() = %f\n", t);

    if (t < 50 + 1e-3) {
        result = 1;
    }

    glfwTerminate();

#ifdef REPORT_RESULT
    REPORT_RESULT(result);
#endif

    return 0;
}