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
struct TYPE_2__ {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 TYPE_1__* g ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ ,int*,int*) ; 

int get_scale_factor() {
    int window_width, window_height;
    int buffer_width, buffer_height;
    glfwGetWindowSize(g->window, &window_width, &window_height);
    glfwGetFramebufferSize(g->window, &buffer_width, &buffer_height);
    int result = buffer_width / window_width;
    result = MAX(1, result);
    result = MIN(2, result);
    return result;
}