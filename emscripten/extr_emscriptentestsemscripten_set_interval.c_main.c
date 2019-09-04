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
 int /*<<< orphan*/  EM_ASM (int) ; 
 int* Module ; 
 int /*<<< orphan*/  emscripten_set_interval (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  intervalId ; 
 int /*<<< orphan*/  tick ; 

int main()
{
	intervalId = emscripten_set_interval(tick, 100, (void*)1);
	EM_ASM(Module['noExitRuntime'] = 1);
}