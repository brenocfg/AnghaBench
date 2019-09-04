#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float const r; float const g; float const b; int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ Thread ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 scalar_t__ fabs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float const,float const,float const,float) ; 
 float glfwGetTime () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 scalar_t__ running ; 
 int /*<<< orphan*/  sin (float) ; 

__attribute__((used)) static int thread_main(void* data)
{
    const Thread* thread = data;

    glfwMakeContextCurrent(thread->window);
    glfwSwapInterval(1);

    while (running)
    {
        const float v = (float) fabs(sin(glfwGetTime() * 2.f));
        glClearColor(thread->r * v, thread->g * v, thread->b * v, 0.f);

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(thread->window);
    }

    glfwMakeContextCurrent(NULL);
    return 0;
}